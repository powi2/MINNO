//
//  PITrimOptions.h
//  PITrimOptions
//
//  Created by Greg Prewitt for Power Integrations on 02/09/2014.
//  Copyright (c) 2014 Power Integrations. All rights reserved.
//
// Version History:
//   v1.0.0 - 13Feb2014 by G.Prewitt - Initial release.
//   v1.1.0 - 03Mar2014 by G.Prewitt - Made Part ID comparision case insensitive.
//   v1.2.0 - 19Mar2014 by G.Prewitt - Fixed bug where Read() returned non-zero
//            when no values found for specified Part ID.
//   v1.3.0 - 20Jan2016 by G.Prewitt - Increased CSV line buffer to accomodate
//            long header lines, increased allowable columns, and added guard
//            against line truncation on read.
//   v1.3.1 - 21Jan2016 by G.Prewitt - Rename MAX_FIELDS and MAX_LINE_LENGTH
//            macros to avoid collision with other macros in test programs.


#ifndef __PITRIMOPTIONS_H__
#define __PITRIMOPTIONS_H__

#define MAX_TRIMOPS_FIELDS 256  // maximumn number of CSV fields/columns supported
#define MAX_TRIMOPS_LENGTH 4096  // maximum number of characters read from CSV line

class PITrimOptions
{
public:
  // define public class variables
  
  // define public class properties
  char* GetFamily (void);
  char* GetRevision (void);
  char* GetDateStamp (void);
  int GetFieldCount (void);
  char* GetHeader (const int index);
  char* GetUnit (const int index);
  char* GetTrimOpAsString (const int index);
  long GetTrimOpAsLong (const int index);
  double GetTrimOpAsDouble (const int index);
  void RunTestCases (void);
  
  // define public class methods
  PITrimOptions (void);
  ~PITrimOptions( void);
  int Read (const char* csvfile, const char* partid);
  
private:
  // define private class variables
  int m_fields;
  char m_family[80];
  char m_revision[40];
  char m_datestamp[40];
  bool m_state_trimops;  // parsing context flag that within TRIMOPS block
  bool m_trimops_found;
  char* m_family_fields[2];
  char* m_revision_fields[2];
  char* m_date_fields[2];
  char* m_header_fields[MAX_TRIMOPS_FIELDS];
  char* m_unit_fields[MAX_TRIMOPS_FIELDS];
  char* m_trimops_fields[MAX_TRIMOPS_FIELDS];
  bool m_read_oneshot;
  
  // define private class methods
  void Initialize (void);
  void ParseLine (char* line, const char* partid);
  int ParseFields(char* line, char* field[], int maxfields);
  void ParseSpecificField(char* line, char field[], size_t field_size, int field_index);
  char* StripEol (char* str);
  char* TrimLeft (char* str);
  char* TrimRight (char* str);
  char* Trim (char* str);
  bool StartsWith(const char* str, const char* pre);
  bool StartsWithInsensitive (const char* str, const char* pre);
  bool StrMatchInsensitive (const char* lhs, const char* rhs);
  size_t strlcpy(char *dst, const char *src, size_t siz);
  size_t strlcat(char *dst, const char *src, size_t siz);
};

#endif /* defined(__PITRIMOPTIONS_H__) */
