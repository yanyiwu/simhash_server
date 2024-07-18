#include <unistd.h>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <string.h>
#include "Husky/ThreadPoolServer.hpp"
#include "simhash/Simhasher.hpp"

using namespace Husky;
using namespace simhash;

const size_t PORT = 11201;
const size_t THREAD_NUMBER = 4;
const size_t QUEUE_MAX_SIZE = 256;
const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const MODEL_PATH = "./dict/hmm_model.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORDS_PATH = "./dict/stop_words.utf8";
const size_t TOP_N = 5;

class ReqHandler: public IRequestHandler
{
    public:
        ReqHandler(const string& dictPath, const string& modelPath, const string& idfPath, const string& stopwordsPath): _simasher(dictPath, modelPath, idfPath, stopwordsPath){};
        virtual ~ReqHandler(){};
    public:
        virtual bool do_GET(const HttpReqInfo& httpReq, string& strSnd) const
        {
            string s, tmp;
            httpReq.GET("s", tmp);
            URLDecode(tmp, s);
            uint64_t u64;
            bool ok = _simasher.make(s, TOP_N, u64);
            strSnd << u64;
            return ok;
        }
        virtual bool do_POST(const HttpReqInfo& httpReq, string& strSnd) const
        {
            const string& s = httpReq.getBody();
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
    ThreadPoolServer server(THREAD_NUMBER, QUEUE_MAX_SIZE, PORT, reqHandler);
    server.start();
    return EXIT_SUCCESS;
}

