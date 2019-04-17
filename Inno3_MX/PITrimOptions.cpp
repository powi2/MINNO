//
//  PITrimOptions.cpp
//  PITrimOptions
//
//  Created by Greg Prewitt for Power Integrations on 02/09/2014.
//  Copyright (c) 2014 Power Integrations. All rights reserved.
//

#include "asl.h"  // *** You must include asl.h to compile into a test program ***
#include <assert.h>
#include <ctype.h>
#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PITrimOptions.h"


/*-----------------------------------------------------------------------*/
/* PITrimOptions - Class constructor method.                             */
/*-----------------------------------------------------------------------*/
PITrimOptions::PITrimOptions (void)
{
  Initialize();
}


/*-----------------------------------------------------------------------*/
/* ~PITrimOptions - Class destructor method.                             */
/*-----------------------------------------------------------------------*/
PITrimOptions::~PITrimOptions (void)
{
}


/*-----------------------------------------------------------------------*/
/* Initialize - Initializes member variables.                            */
/*-----------------------------------------------------------------------*/
void PITrimOptions::Initialize (void)
{
  m_fields = 0;
  m_state_trimops = false;
  m_trimops_found = false;
  m_read_oneshot = false;
  
  // initialize arrays of parsed field points to null
  memset(m_family_fields, 0, sizeof(m_family_fields));
  memset(m_revision_fields, 0, sizeof(m_revision_fields));
  memset(m_date_fields, 0, sizeof(m_date_fields));
  memset(m_header_fields, 0, sizeof(m_header_fields));
  memset(m_unit_fields, 0, sizeof(m_unit_fields));
  memset(m_trimops_fields, 0, sizeof(m_trimops_fields));
}


/*-----------------------------------------------------------------------*/
/* Read - Reads the specified CSV file searching for the trim options    */
/* for the specified part ID.  The implementor should check the return   */
/* value.  If the return value is zero, then either the CSV file could   */
/* not be opened or no trim options could be found for the specified     */
/* part ID.  Additionally, you should not attempt to lookup trim         */
/* fields of index greater than (fields -1).                             */
/*                                                                       */
/* :param csvfile: path/filename of trim options CSV file to parse       */
/* :param partid: part ID for which trim options should be parsed        */
/* :return: count of trim options header/value columns parsed or zero    */
/*-----------------------------------------------------------------------*/
int PITrimOptions::Read (const char* csvfile, const char* partid)
{
  // implement one-shot interlock for read operation (because of all the dynamic variable allocation)
  if (m_read_oneshot)
    fprintf(stderr,"PITrimOptions::Read: Multiple read operations are not allowed.");
  else m_read_oneshot = true;
  
  if (_access(csvfile,04) == -1)
  {
    fprintf(stderr,"PITrimOptions::Read: Trim option data file (%s) does not exist.\r\n",csvfile);
    return(0);
  }
  
  FILE* fp = NULL;
  if ((fp = fopen(csvfile,"r")) == NULL)
  {
    fprintf(stderr,"PITrimOptions::Read: Unable to open trim options data file (%s).\r\n",csvfile);
    return(0);
  }
  
  // read and process each line of trim options file
  int ln = 0;  // line number counter
  size_t length = 0;
  char line[MAX_TRIMOPS_LENGTH];
  while (fgets(line,sizeof(line),fp) != NULL)
  {
    // detect line truncations and return a failure code
    ln++;
    if (strlen(line) == MAX_TRIMOPS_LENGTH-1)
    {
      fprintf(stderr,"PITrimOptions::Read: Line truncation reading file (%s) at line %d.\r\n",csvfile,ln);
      return(0);
    }

    StripEol(line);  // remove end-of-line characters returned by fgets()
    
    // ignore and skip uninteresting lines
    if (StartsWithInsensitive(TrimLeft(line), "COMMENT")) { continue; }  // ignore comment lines
    if (StartsWithInsensitive(TrimLeft(line), "HISTORY")) { continue; }  // ignore history lines
    if (StartsWithInsensitive(TrimLeft(line),",")) { continue; }  // ignore lines without keyword (blank Excel lines)
    
    // watch for TRIMOPS section, setting the parser state flag accordingly
    if (StartsWithInsensitive(TrimLeft(line), "BEGIN TRIMOPS")) { m_state_trimops = true; continue; }
    if (StartsWithInsensitive(TrimLeft(line), "END TRIMOPS")) { m_state_trimops = false; continue; }

    // if we make it to here, then we need to parse for values
    ParseLine(line, partid);
  }
  fclose(fp);

  // if trim options were not found for the specified PartID, then return zero
  if (!m_trimops_found) { m_fields = 0; }
  return(m_fields);
}


/*-----------------------------------------------------------------------*/
/* ParseLine - Extracts values from interesting lines of the Trim        */
/* Options CSV format.  This method should not be called for             */
/* uninteresting lines like COMMENT.                                     */
/*                                                                       */
/* :param line: single line read from CSV with EOL characters stripped   */
/* :param partid: part ID for which trim options are sought              */
/*-----------------------------------------------------------------------*/
void PITrimOptions::ParseLine (char* line, const char* partid)
{
  //printf("DEBUG - Parsing: %s\r\n",line);
  
  if (StartsWithInsensitive(TrimLeft(line), "FAMILY"))
  {
    ParseFields(line, m_family_fields, 2);
  }
  else if (StartsWithInsensitive(TrimLeft(line), "REV"))
  {
    ParseFields(line, m_revision_fields, 2);
  }
  else if (StartsWithInsensitive(TrimLeft(line), "DATE"))
  {
    ParseFields(line, m_date_fields, 2);
  }
  else if (StartsWithInsensitive(TrimLeft(line), "HEADER"))
  {
    m_fields = ParseFields(line, m_header_fields, MAX_TRIMOPS_FIELDS);
  }
  else if (StartsWithInsensitive(TrimLeft(line), "UNIT"))
  {
    ParseFields(line, m_unit_fields, MAX_TRIMOPS_FIELDS);
  }
  else if ((m_state_trimops) && (StartsWithInsensitive(TrimLeft(line), "TRIMOPS")))
  {
    if (!m_trimops_found)
    { // search through this trim options line to see if matches the specified partid
      char fieldbuff[40];
      ParseSpecificField(line, fieldbuff, sizeof(fieldbuff), 1);
      if (StrMatchInsensitive(fieldbuff, partid))
      { // this line has the trim options for the specified partid, so parse and store all values
        m_trimops_found = true;
        int fields = ParseFields(line, m_trimops_fields, MAX_TRIMOPS_FIELDS);
        if (fields != m_fields)
          fprintf(stderr,"PITrimOptions::ParseLine: CSV file HEADER and TRIMOPS have different number of columns.");
      }
    }
  }
  else
  {
    fprintf(stderr,"ParseLine: Encountered unknown line in trim options file: %s\r\n",line);
  }

  return;
}


/*-----------------------------------------------------------------------*/
/* ParseFields - Extracts values from the supplied CSV line by column.   */
/* The value of each column is stored as a string and an element of the  */
/* field[] array is pointed to each extracted value.                     */
/*                                                                       */
/* :param line: single line read from CSV with EOL characters stripped   */
/* :param field: array of char pointers to which parsed values linked    */
/* :param maxfields: max number of field[] array elements                */
/*-----------------------------------------------------------------------*/
int PITrimOptions::ParseFields(char* line, char* field[], int maxfields)
{
  int fields = 0;
  char fieldbuff[100];
  memset(fieldbuff, 0, sizeof(fieldbuff));
  bool within_quotes = false;
  
  char* lptr = line;
  char* fptr = fieldbuff;
  
  while ((fields < maxfields) && (*lptr != '\0'))
  {
    if ((*lptr == '"') && (!within_quotes)) { within_quotes = true; lptr++; continue; }
    if ((*lptr == '"') && (within_quotes)) { within_quotes = false; lptr++; continue; }
    if ((*lptr == ',') && (!within_quotes))
    { // end of CSV column, so terminate and store the field
      size_t len = strlen(fieldbuff);
      field[fields] = (char*) malloc(len+1);
      char* trimmed = Trim(fieldbuff);
      strlcpy(field[fields], trimmed, len+1);
      fields++;
      //printf("DEBUG - FIELD %d: '%s'\r\n",(fields-1),fieldbuff);
      memset(fieldbuff,0,sizeof(fieldbuff));
      fptr = fieldbuff;
      lptr++;
    }
    else
    { // still within the CSV column, so copy the current character to field buffer
      *fptr = *lptr;
      fptr++;
      lptr++;
    }
  }

  if ((fields < maxfields) && (strlen(fieldbuff) > 0))
  { // ran out of input, last CSV field, before reaching maxfields, typical end of line occurrence
    size_t len = strlen(fieldbuff);
    field[fields] = (char*) malloc(len+1);
    strlcpy(field[fields], Trim(fieldbuff), len+1);
    fields++;
    //printf("DEBUG - FIELD %d: '%s'\r\n",(fields-1),fieldbuff);
  }
  return(fields);
}


/*-----------------------------------------------------------------------*/
/* ParseSpecificField - Extracts one specific field from the supplied    */
/* CSV line as defined by the field_index parameter.  In practice, this  */
/* method is used to get the Part ID field from TRIMOPS lines to find    */
/* a specific trim options line.                                         */
/*                                                                       */
/* NOTE: The field[] parameter here is a standard C-language char array  */
/* string variable and not at all like the field[] array of char         */
/* pointers used in calls to ParseFields() method.                       */
/*                                                                       */
/* :param line: single line read from CSV with EOL characters stripped   */
/* :param field: array of char pointers to which parsed values linked    */
/* :param maxfields: max number of field[] array elements                */
/*-----------------------------------------------------------------------*/
void PITrimOptions::ParseSpecificField(char* line, char field[], size_t field_size, int field_index)
{
  int fields = 0;
  char fieldbuff[100];
  memset(fieldbuff, 0, sizeof(fieldbuff));
  bool within_quotes = false;
  
  char* lptr = line;
  char* fptr = fieldbuff;
  
  while ((fields <= field_index) && (*lptr != '\0'))
  {
    if ((*lptr == '"') && (!within_quotes)) { within_quotes = true; lptr++; continue; }
    if ((*lptr == '"') && (within_quotes)) { within_quotes = false; lptr++; continue; }
    if ((*lptr == ',') && (!within_quotes))
    { // end of CSV column, so terminate and store the field if it is the specific field requested
      if (fields == field_index)
        break;  // found the end of the specified field, so break out of while loop and stop
      fields++;
      //printf("DEBUG - FIELD %d: '%s'\r\n",(fields-1),fieldbuff);
      memset(fieldbuff,0,sizeof(fieldbuff));
      fptr = fieldbuff;
      lptr++;
    }
    else
    { // still within the CSV column, so copy the current character to field buffer
      *fptr = *lptr;
      fptr++;
      lptr++;
    }
  }
  
  if ((fields == field_index) && (strlen(fieldbuff) > 0))
  {
    strlcpy(field, Trim(fieldbuff), field_size);
    //printf("DEBUG - REQUESTED FIELD: '%s'\r\n",fieldbuff);
  }
  return;
}


/*-----------------------------------------------------------------------*/
/* GetFamily - Returns the family description string parsed from CSV.    */
/* This is the value of the column following the FAMILY keyword in CSV.  */
/*                                                                       */
/* :return: trim options data file FAMILY description string.            */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::GetFamily (void)
{
  assert((m_family_fields[0] != NULL) && (m_family_fields[1] != NULL));
  return(m_family_fields[1]);
}


/*-----------------------------------------------------------------------*/
/* GetRevision - Returns the revision string parsed from CSV.            */
/* This is the value of the column following the REV keyword in CSV.     */
/*                                                                       */
/* :return: trim options data file REV revision string.                  */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::GetRevision (void)
{
  assert((m_revision_fields[0] != NULL) && (m_revision_fields[1] != NULL));
  return(m_revision_fields[1]);
}


/*-----------------------------------------------------------------------*/
/* GetDateStamp - Returns the date stamp string parsed from CSV.         */
/* This is the value of the column following the DATE keyword in CSV.    */
/*                                                                       */
/* :return: trim options data file DATE time stamp string.               */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::GetDateStamp (void)
{
  assert((m_date_fields[0] != NULL) && (m_date_fields[1] != NULL));
  return(m_date_fields[1]);
}


/*-----------------------------------------------------------------------*/
/* GetFieldCount - Returns to count of header and trim option columns    */
/* detected and parsed from CSV.  The number of header columns and trim  */
/* option columns must be equal.                                         */
/*                                                                       */
/* :return: count of trim options header/value columns parsed.           */
/*-----------------------------------------------------------------------*/
int PITrimOptions::GetFieldCount (void)
{
  return(m_fields);
}


/*-----------------------------------------------------------------------*/
/* GetHeader - Returns the value of the specified HEADER field.          */
/*                                                                       */
/* NOTE: The index parameter is zero based (like all other C arrays)     */
/* and, therefore, index zero will return the CSV keyword column.        */
/*                                                                       */
/* :param index: zero based index to trim options header field.          */
/* :return: trim option header for specified index                       */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::GetHeader (const int index)
{
  if ((index < 0) || (index > m_fields))
    fprintf(stderr,"GetHeader: Programmer error, index is out of range.\r\n");
  assert(index >= 0);
  assert(index < m_fields);
  assert(m_header_fields[0] != NULL);
  return(m_header_fields[index]);
}


/*-----------------------------------------------------------------------*/
/* GetUnit - Returns the value of the specified UNIT field.              */
/*                                                                       */
/* NOTE: The index parameter is zero based (like all other C arrays)     */
/* and, therefore, index zero will return the CSV keyword column.        */
/*                                                                       */
/* :param index: zero based index to trim options unit field.            */
/* :return: trim option unit for specified index, may be empty string    */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::GetUnit (const int index)
{
  if ((index < 0) || (index > m_fields))
    fprintf(stderr,"GetHeader: Programmer error, index is out of range.\r\n");
  assert(index >= 0);
  assert(index < m_fields);
  assert(m_unit_fields[0] != NULL);
  return(m_unit_fields[index]);
}


/*-----------------------------------------------------------------------*/
/* GetTrimOpAsString - Returns the value of the specified TRIMOPS field  */
/* for the TRIMOPS line that matched the specified 'part ID' as a string.*/
/*                                                                       */
/* NOTE: The index parameter is zero based (like all other C arrays)     */
/* and, therefore, index zero will return the CSV keyword column.        */
/*                                                                       */
/* :param index: zero based index to trim options value field.           */
/* :return: trim option value for specified index                        */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::GetTrimOpAsString (const int index)
{
  if ((index < 0) || (index > m_fields))
    fprintf(stderr,"GetHeader: Programmer error, index is out of range.\r\n");
  assert(index >= 0);
  assert(index < m_fields);
  assert(m_trimops_fields[0] != NULL);
  return(m_trimops_fields[index]);
}


/*-----------------------------------------------------------------------*/
/* GetTrimOpAsLong - Convenience method to retrieve the specified        */
/* TRIMOPS field for the TRIMOPS line that matched the specified         */
/* 'part ID' converted to a long integer type.                           */
/*                                                                       */
/* NOTE: The index parameter is zero based (like all other C arrays)     */
/* and, therefore, index zero will return the CSV keyword column.        */
/*                                                                       */
/* NOTE: This method may cause/throw a runtime error if the trim option  */
/* value can not be successfully converted to an integer.  It is up to   */
/* the test engineer to know the structure of the trim options data file */
/* and decode the columns to string/long/double values as appropriate.   */
/*                                                                       */
/* :param index: zero based index to trim options value field.           */
/* :return: trim option value for specified index converted to integer   */
/*-----------------------------------------------------------------------*/
long PITrimOptions::GetTrimOpAsLong (const int index)
{
  if ((index < 0) || (index > m_fields))
    fprintf(stderr,"GetHeader: Programmer error, index is out of range.\r\n");
  assert(index >= 0);
  assert(index < m_fields);
  assert(m_trimops_fields[index] != NULL);
  return(strtol(m_trimops_fields[index], NULL, 10));
}


/*-----------------------------------------------------------------------*/
/* GetTrimOpAsDouble - Convenience method to retrieve the specified      */
/* TRIMOPS field for the TRIMOPS line that matched the specified         */
/* 'part ID' converted to a double type.                                 */
/*                                                                       */
/* NOTE: The index parameter is zero based (like all other C arrays)     */
/* and, therefore, index zero will return the CSV keyword column.        */
/*                                                                       */
/* NOTE: This method may cause/throw a runtime error if the trim option  */
/* value can not be successfully converted to an integer.  It is up to   */
/* the test engineer to know the structure of the trim options data file */
/* and decode the columns to string/long/double values as appropriate.   */
/*                                                                       */
/* :param index: zero based index to trim options value field.           */
/* :return: trim option value for specified index converted to double    */
/*-----------------------------------------------------------------------*/
double PITrimOptions::GetTrimOpAsDouble (const int index)
{
  if ((index < 0) || (index > m_fields))
    fprintf(stderr,"GetHeader: Programmer error, index is out of range.\r\n");
  assert(index >= 0);
  assert(index < m_fields);
  assert(m_trimops_fields[index] != NULL);
  return(strtod(m_trimops_fields[index], NULL));
}


/*-----------------------------------------------------------------------*/
/* RunTestCases - This function is for developer use only and should     */
/* never be called when implemented into a test program.  This function  */
/* can be further extended as needed for validating methods.             */
/*-----------------------------------------------------------------------*/
void PITrimOptions::RunTestCases (void)
{
  printf("TestCase: StartsWithInsensitive(\"%s\",\"%s\")\r\n","FAMILY,InnoSwitch,,,","FAMILY");
  printf("--> %s\r\n",(StartsWithInsensitive("FAMILY,InnoSwitch,,,", "FAMILY") ? "TRUE" : "FALSE"));
  
  printf("TestCase: StartsWithInsensitive(\"%s\",\"%s\")\r\n","FAMILY ,InnoSwitch,,,","FAMILY");
  printf("--> %s\r\n",(StartsWithInsensitive("FAMILY ,InnoSwitch,,,", "FAMILY") ? "TRUE" : "FALSE"));

  printf("TestCase: StartsWithInsensitive(\"%s\",\"%s\")\r\n"," FAMILY,InnoSwitch,,,","FAMILY");
  printf("--> %s\r\n",(StartsWithInsensitive(" FAMILY,InnoSwitch,,,", "FAMILY") ? "TRUE" : "FALSE"));
  
  printf("TestCase: StartsWithInsensitive(TrimLeft(\"%s\"),\"%s\")\r\n"," FAMILY,InnoSwitch,,,","FAMILY");
  printf("--> %s\r\n",(StartsWithInsensitive(TrimLeft(" FAMILY,InnoSwitch,,,"), "FAMILY") ? "TRUE" : "FALSE"));

  printf("TestCase: StartsWithInsensitive(\"%s\",\"%s\")\r\n","family,InnoSwitch,,,","FAMILY");
  printf("--> %s\r\n",(StartsWithInsensitive("family,InnoSwitch,,,", "FAMILY") ? "TRUE" : "FALSE"));
  
  // test cases for case insensitive Part ID comparision
  const char lhs1[] = "ABC123K";  const char rhs1[] = "abc123k";
  printf("TestCase: StrMatchInsensitive(\"%s\",\"%s\")\r\n",lhs1,rhs1);
  printf("--> %s\r\n",(StrMatchInsensitive(lhs1,rhs1) ? "TRUE" : "FALSE"));

  const char lhs2[] = "abc123k";  const char rhs2[] = "abc123k";
  printf("TestCase: StrMatchInsensitive(\"%s\",\"%s\")\r\n",lhs2,rhs2);
  printf("--> %s\r\n",(StrMatchInsensitive(lhs2,rhs2) ? "TRUE" : "FALSE"));

  const char lhs3[] = "ABC123K";  const char rhs3[] = "ABC123K";
  printf("TestCase: StrMatchInsensitive(\"%s\",\"%s\")\r\n",lhs3,rhs3);
  printf("--> %s\r\n",(StrMatchInsensitive(lhs3,rhs3) ? "TRUE" : "FALSE"));

  const char lhs4[] = "ABC1234";  const char rhs4[] = "abc123";
  printf("TestCase: StrMatchInsensitive(\"%s\",\"%s\")\r\n",lhs4,rhs4);
  printf("--> %s\r\n",(StrMatchInsensitive(lhs4,rhs4) ? "TRUE" : "FALSE"));

  const char lhs5[] = "ABC123";  const char rhs5[] = "abc1234";
  printf("TestCase: StrMatchInsensitive(\"%s\",\"%s\")\r\n",lhs5,rhs5);
  printf("--> %s\r\n",(StrMatchInsensitive(lhs5,rhs5) ? "TRUE" : "FALSE"));

  const char lhs6[] = "ABC123K ";  const char rhs6[] = "abc123k";
  printf("TestCase: StrMatchInsensitive(\"%s\",\"%s\")\r\n",lhs6,rhs6);
  printf("--> %s\r\n",(StrMatchInsensitive(lhs6,rhs6) ? "TRUE" : "FALSE"));

  const char lhs7[] = "ABC123k";  const char rhs7[] = "ABC123K ";
  printf("TestCase: StrMatchInsensitive(\"%s\",\"%s\")\r\n",lhs7,rhs7);
  printf("--> %s\r\n",(StrMatchInsensitive(lhs7,rhs7) ? "TRUE" : "FALSE"));

  printf("");
}


/*-----------------------------------------------------------------------*/
/* StripEol - Removes either or both carriage-return and line-feed       */
/* end-of-line characters from the supplied string.  The EOL characters  */
/* are stripped simply by overwriting them with string termination       */
/* characters, therefore, the supplied string is modified.               */
/*                                                                       */
/* :param str: string to strip EOL characters from                       */
/* :returns: pointer to the modified string supplied as parameter        */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::StripEol (char* str)
{
  char* end = str + strlen(str);
  while ((*(end-1) == '\r') || (*(end-1) == '\n'))
  {
    end--;
    *end = '\0';
  }
  return(str);
}


/*-----------------------------------------------------------------------*/
/* TrimLeft - Searches to the first non-space character position in the  */
/* supplied string and returns a pointer into the same string.           */
/*                                                                       */
/* :param str: pointer to string to be trimmed                           */
/* :returns: pointer to a position in same string supplied as parameter  */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::TrimLeft (char* str)
{
  if (strlen(str) < 1) { return(str); }
  while (isspace(*str)) { str++; }
  return(str);
}


/*-----------------------------------------------------------------------*/
/* TrimRight - Removes trailing white space characters from the supplied */
/* string.  The whitespace characters are removed simply by overwriting  */
/* them with string termination characters, therefore, the supplied      */
/* string is modified.                                                   */
/*                                                                       */
/* :param str: pointer to string to be trimmed                           */
/* :returns: pointer to the modified string supplied as parameter        */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::TrimRight (char* str)
{
  if (strlen(str) < 1) { return(str); }
  char* end = str + strlen(str);
  while (isspace(*(end - 1))) { end--; }
  *end = '\0';
  return(str);
}


/*-----------------------------------------------------------------------*/
/* Trim returns a pointer into the supplied string beyond any leading    */
/* whitespace characters and with trailing whitespace characters         */
/* removed.  Note that the original string is modified.                  */
/*                                                                       */
/* :param str: pointer to string to be trimmed                           */
/* :returns: pointer to the modified string supplied as parameter        */
/*-----------------------------------------------------------------------*/
char* PITrimOptions::Trim (char* str)
{
  if (strlen(str) < 1) { return(str); }
  return(TrimRight(TrimLeft(str)));
}


/*-----------------------------------------------------------------------*/
/* StartsWith - Determines if the supplied string starts with the        */
/* specified prefix.  This comparision is carried out case sensitive.    */
/*                                                                       */
/* :param str: string to be matched                                      */
/* :param pre: prefix string to match against start of 'str' parameter   */
/* :returns: true if the string begins with the prefix, otherwise false  */
/*-----------------------------------------------------------------------*/
bool PITrimOptions::StartsWith (const char* str, const char* pre)
{
  size_t str_len = strlen(str);
  size_t pre_len = strlen(pre);
  if (str_len < pre_len)
    return(false);
  return(strncmp(str, pre, pre_len) == 0);
}


/*-----------------------------------------------------------------------*/
/* StartsWithInsensitive - Determines if the supplied string starts with */
/* the specified prefix.  This comparision is carried out case           */
/* insensitive.                                                          */
/*                                                                       */
/* :param str: string to be matched                                      */
/* :param pre: prefix string to match against start of 'str' parameter   */
/* :returns: true if the string begins with the prefix, otherwise false  */
/*-----------------------------------------------------------------------*/
bool PITrimOptions::StartsWithInsensitive (const char* str, const char* pre)
{
  size_t str_len = strlen(str);
  size_t pre_len = strlen(pre);
  if (str_len < pre_len)
    return(false);
  for (size_t i = 0; i < pre_len; i++)
    if (toupper(str[i]) != toupper(pre[i]))
      return(false);
  return(true);
}


/*-----------------------------------------------------------------------*/
/* StrMatchInsensitive - Determines if the two supplied strings, when    */
/* compared case-insensitive, match each other.                          */
/*                                                                       */
/* :param lhs: left-hand string to be compared                           */
/* :param rhs: right-hand string to be compared                          */
/* :returns: true if the strings match case-insensitive, otherwise false */
/*-----------------------------------------------------------------------*/
bool PITrimOptions::StrMatchInsensitive (const char* lhs, const char* rhs)
{
  size_t lhs_len = strlen(lhs);
  size_t rhs_len = strlen(rhs);
  if (lhs_len != rhs_len)
    return(false);
  for (size_t i = 0; i < lhs_len; i++)
    if (toupper(lhs[i]) != toupper(rhs[i]))
      return(false);  // string do not match
  return(true);  // strings match
}


/* --------------------------------------------------------------------------
 * strlcpy - Safe alternative to strcpy() function used throughout
 *     Framework code.  This function is taken directly from the OpenBSD
 *     strlcpy() function.  Given the correct size of the destination
 *     C-string, this function will not overrun the destination
 *     buffer and guarantees a null terminated string [G.Prewitt 13Dec2013].
 *     -  At most siz-1 characters will be copied.
 *     -  The dst string is always null terminated (unless siz == 0).
 *     -  Returns equivalent of strlen(src) to allow truncation detection.
 *     -  If retval >= siz, then truncation occurred.
 * --------------------------------------------------------------------------
 *
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
size_t PITrimOptions::strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
  
	/* Copy as many bytes as will fit */
	if (n != 0)
  {
		while (--n != 0)
    {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}
  
	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0)
  {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}
  
	return(s - src - 1);	/* count does not include NUL */
}


/* --------------------------------------------------------------------------
 * strlcat - Safe alternative to strcat() function used throughout
 *     Framework code.  This function is taken directly from the OpenBSD
 *     strlcat() function.  Given the correct size of the destination
 *     C-string, this function will not overrun the destination
 *     buffer and all but guarantees a null terminated string [G.Prewitt 13Dec2013].
 *     -  Unlike strncat, siz is the full size of dst (not just the space left).
 *     -  At most siz-1 characters will be copied.
 *     -  The dst string is always null terminated (unless siz <= strlen(dst)).
 *     -  Returns equivalent of strlen(src) to allow truncation detection.
 *     -  If retval >= siz, then truncation occurred.
 * --------------------------------------------------------------------------
 *
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
size_t PITrimOptions::strlcat(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;
  
	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	n = siz - dlen;
  
	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
  
	return(dlen + (s - src));	/* count does not include NUL */
}
