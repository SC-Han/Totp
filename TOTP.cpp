#include <iostream>
#include <iomanip>
#include <chrono>

#include <cstring>
#include <openssl/hmac.h>
#include <vector>
#include <thread>
#include <sstream>

//TOTP�� �����ϴ� �Լ� 
std::string generateTOTP(const std::string& secretKey, uint64_t timeStep = 10, uint8_t codeDigits = 6) {

    // ���� �ð��� TimeStep ���� ���� timeValue�� ���
    auto currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    uint64_t timeValue = currentTime / timeStep;

    //timeValue�� 8����Ʈ �޽����� ��ȯ
    unsigned char msg[8];
    for (int i = 7; i >= 0; --i) {
        msg[i] = timeValue & 0xFF;
        timeValue >>= 8;
    }

    //���Ű�� ���� �����ͷ� ��ȯ������
    std::vector<char> decodedKey(secretKey.begin(), secretKey.end());

    //HMAC �Լ��� ����Ͽ� �ؽð� ����
    unsigned char hash[20];
    HMAC(EVP_sha1(), &decodedKey[0], decodedKey.size(), msg, 8, hash, NULL);


    //�ؽð����� TOTP�� �ڵ带 ��������
    int offset = hash[19] & 0x0F;
    unsigned int truncatedHash = (hash[offset] & 0x7F) << 24
        | (hash[offset + 1] & 0xFF) << 16
        | (hash[offset + 2] & 0xFF) << 8
        | (hash[offset + 3] & 0xFF);

    truncatedHash %= 1000000;


    // �ڵ带 6�ڸ� ���ڿ��� ��ȯ
    std::ostringstream result;
    result << std::setw(codeDigits) << std::setfill('0') << truncatedHash;

    return result.str();
}

int main() {

    // ����� ��� Ű 
    std::string secretKey = "JBSWY3DPEHPK3PXP";

    while (true) {
        //TOTP �ڵ� ����45
        std::string totpCode = generateTOTP(secretKey);

        //������ TOTP �ڵ� ���
        std::cout << "TOTP �ڵ�: " << totpCode << std::endl;

        // 10�ʸ��� TOTP�� ���� 
        std::this_thread::sleep_for(std::chrono::seconds(10)); // 10�ʷ� ����
    }

    return 0;
}