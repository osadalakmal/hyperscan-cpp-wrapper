#include "hs_wrapper.h"
#include <string.h>

namespace 
{

    bool
    compile(HyperScanDatabase::ScanMode scanMode,
            std::vector<char*> patterns,
            std::vector<unsigned int> flags,
            std::vector<unsigned int> ids,
            hs_database** database,
            hs_scratch** scratch)
    {
      hs_compile_error_t* compileError;
      if (hs_compile_multi(&patterns[0],
                           &flags[0],
                           &ids[0],
                           patterns.size(),
                           (scanMode == HyperScanDatabase::ScanMode::STREAM
                              ? HS_MODE_STREAM
                              : HS_MODE_BLOCK),
                           nullptr,
                           database,
                           &compileError) != HS_SUCCESS) {
        fprintf(
          stderr, "ERROR: Unable to compile patterns: %s\n", compileError->message);
        hs_free_compile_error(compileError);
        hs_free_database(*database);
        return false;
      }
      if (hs_alloc_scratch(*database, scratch) != HS_SUCCESS) {
        fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
        hs_free_database(*database);
        return false;
      }
      return true;
    }
} // anonymous namespace

HyperScanDatabase::HyperScanDatabase(ScanMode scanMode)
  : m_scanMode(scanMode)
  , m_database(nullptr)
  , m_scratch(nullptr)
{
  m_ids.push_back(0);
}

HyperScanDatabase::~HyperScanDatabase()
{
  if (m_database) {
    hs_free_database(m_database);
  }
  if (m_scratch) {
    hs_free_scratch(m_scratch);
  }
  for (auto pattern : m_patterns) {
    delete[] pattern;
  }
}

int
HyperScanDatabase::addPattern(const char* pattern, int flags)
{
  char* d_pattern = new char[strlen(pattern) + 1];
  strncpy(d_pattern, pattern, strlen(pattern) + 1);
  m_patterns.push_back(d_pattern);
  m_flags.push_back(flags);
  m_ids.push_back(m_ids.back()++);
  return m_patterns.size() - 1;
}

int
HyperScanDatabase::scan(const char* data1, size_t dataSize, EventHandler eventHandler)
{
  int rc = HS_SUCCESS;
  if (!m_compiled) compile(m_scanMode, m_patterns, m_flags, m_ids, &m_database, &m_scratch);
  if ((rc = hs_scan(
         m_database, data1, dataSize, 0, m_scratch, eventHandler, nullptr)) !=
      HS_SUCCESS) {
    fprintf(
      stderr, "ERROR: Unable to scan input buffer. rc = %d. Exiting.\n", rc);
  }
  return rc;
}
