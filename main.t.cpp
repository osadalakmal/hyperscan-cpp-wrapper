#include "hs_wrapper.h"
#include <gtest/gtest.h>
#include <hs/hs.h>
#include <functional>

using namespace ::testing;

namespace {

static bool isFound = false;

static int
eventHandler(unsigned int id,
             unsigned long long from,
             unsigned long long to,
             unsigned int flags,
             void* ctx)
{
  isFound = true;
  return 0;
}
}

TEST(EventBucketMain, EventBucket)
{
  const char* input = "AAAA";
  HyperScanDatabase hsdb(HyperScanDatabase::ScanMode::BLOCK);
  hsdb.addPattern("AA", HS_FLAG_DOTALL);
  isFound = false;
  hsdb.scan(input, strlen(input), eventHandler);
  ASSERT_TRUE(isFound);
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
