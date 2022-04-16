
#include <iostream>
#include "Poco/MD5Engine.h"
 #include "Poco/DigestStream.h"

int main(int argc, char const *argv[])
{
    std::cout << "hello world" << std::endl;

    Poco::MD5Engine md5;
    Poco::DigestOutputStream dos(md5);
    dos << "i am test md5 tool from poco";
    dos.close();
    std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;
    return 0;
}
