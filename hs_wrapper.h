#ifndef HS_WRAPPER_H_DEFINED
#define HS_WRAPPER_H_DEFINED

#include <hs/hs.h>
#include <memory>
#include <string>
#include <vector>

class HyperScanDatabase {
public:
    typedef match_event_handler EventHandler;
    enum class ScanMode {
        BLOCK,
        STREAM
    };
    HyperScanDatabase(ScanMode scanMode);
    ~HyperScanDatabase();
    int addPattern(const char* pattern, int flags);
    int scan(const char* data, size_t dataSize, EventHandler);
private:
    std::vector<char*> m_patterns;
    std::vector<unsigned int> m_flags;
    std::vector<unsigned int> m_ids;
    bool m_compiled = false;
    ScanMode m_scanMode;
    hs_database_t* m_database;
    hs_scratch_t* m_scratch;
};

#endif // HS_WRAPPER_H_DEFINED