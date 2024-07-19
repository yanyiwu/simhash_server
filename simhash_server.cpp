#include <unistd.h>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <string.h>
#include "thread_pool_server.h"
#include "simhash/Simhasher.hpp"

using namespace husky;
using namespace simhash;

const size_t PORT = 11201;
const size_t THREAD_NUMBER = 4;
const char* const DICT_PATH = "./submodules/simhash/submodules/cppjieba/dict/jieba.dict.utf8";
const char* const MODEL_PATH = "./submodules/simhash/submodules/cppjieba/dict/hmm_model.utf8";
const char* const IDF_PATH = "./submodules/simhash/submodules/cppjieba/dict/idf.utf8";
const char* const STOP_WORDS_PATH = "./submodules/simhash/submodules/cppjieba/dict/stop_words.utf8";
const size_t TOP_N = 5;

class ReqHandler: public IRequestHandler
{
    public:
        ReqHandler(const string& dictPath, const string& modelPath, const string& idfPath, const string& stopwordsPath): _simasher(dictPath, modelPath, idfPath, stopwordsPath){};
        virtual ~ReqHandler(){};
    public:
        virtual bool DoGET(const HttpReqInfo& httpReq, string& strSnd) 
        {
            string s, tmp;
            httpReq.GET("s", tmp);
            URLDecode(tmp, s);
            uint64_t u64;
            bool ok = _simasher.make(s, TOP_N, u64);
            strSnd << u64;
            return ok;
        }
        virtual bool DoPOST(const HttpReqInfo& httpReq, string& strSnd) 
        {
            const string& s = httpReq.GetBody();
            uint64_t u64;
            bool ok = _simasher.make(s, TOP_N, u64);
            strSnd << u64;
            return ok;
        }
    private:
        Simhasher _simasher;
};

int main(int argc, char* argv[])
{
    ReqHandler reqHandler(DICT_PATH, MODEL_PATH, IDF_PATH, STOP_WORDS_PATH);
    ThreadPoolServer server(THREAD_NUMBER, PORT, reqHandler);
    server.Start();
    return EXIT_SUCCESS;
}

