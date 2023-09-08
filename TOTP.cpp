#include <iostream>
#include <iomanip>
#include <chrono>

#include <cstring>
#include <openssl/hmac.h>
#include <vector>
#include <thread>
#include <sstream>

//TOTP를 생성하는 함수 
std::string generateTOTP(const std::string& secretKey, uint64_t timeStep = 10, uint8_t codeDigits = 6) {

    // 현재 시간을 TimeStep 으로 나눔 timeValue를 계산
    auto currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    uint64_t timeValue = currentTime / timeStep;

    //timeValue를 8바이트 메시지로 변환
    unsigned char msg[8];
    for (int i = 7; i >= 0; --i) {
        msg[i] = timeValue & 0xFF;
        timeValue >>= 8;
    }

    //비밀키를 이진 데이터로 변환시켜줌
    std::vector<char> decodedKey(secretKey.begin(), secretKey.end());

    //HMAC 함수를 사용하여 해시값 생성
    unsigned char hash[20];
    HMAC(EVP_sha1(), &decodedKey[0], decodedKey.size(), msg, 8, hash, NULL);


    //해시값에서 TOTP를 코드를 추출해줌
    int offset = hash[19] & 0x0F;
    unsigned int truncatedHash = (hash[offset] & 0x7F) << 24
        | (hash[offset + 1] & 0xFF) << 16
        | (hash[offset + 2] & 0xFF) << 8
        | (hash[offset + 3] & 0xFF);

    truncatedHash %= 1000000;


    // 코드를 6자리 문자열로 변환
    std::ostringstream result;
    result << std::setw(codeDigits) << std::setfill('0') << truncatedHash;

    return result.str();
}

int main() {

    // 사용할 비밀 키 
    std::string secretKey = "JBSWY3DPEHPK3PXP";

    while (true) {
        //TOTP 코드 생성45
        std::string totpCode = generateTOTP(secretKey);

        //생성된 TOTP 코드 출력
        std::cout << "TOTP 코드: " << totpCode << std::endl;

        // 10초마다 TOTP를 갱신 
        std::this_thread::sleep_for(std::chrono::seconds(10)); // 10초로 수정
    }

    return 0;
}