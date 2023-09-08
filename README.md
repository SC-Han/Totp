# 시간 기반 일회용 비밀번호 TOTP

## Info

OTP는 One Time Password 의 약자로 1회용 인증 수단을 의미합니다.

TOTP는 시간 기반 일회용 비밀번호( Time-Based One-Time Password)의 약자입니다. 
이는 보안 인증을 강화하기 위해 사용되는 기술 중 하나입니다. TOTP는 주로 두 요소 인증(2FA) 시스템에서 사용됩니다.

TOTP를 생성하는 함수와 현재시간을 TimeStep으로 나눠 TimeValue를 계산합니다.
TimeValue를 8바이트 메시지로 변환해줍니다.
또한 비밀키를 이진 데이터로 변환시켜 HMAC 함수를 사용하여 해시값을 생성합니다.
해시값에서 TOTP를 추출하여 코드를 6자리 문자열로 변환시켜주는 코드입니다.

위 코드는 10초마다 인증번호가 바뀌는 시스템입니다.

## HOW?

본 코드는 TOTP.cpp에 본 코드가 작성되어 있습니다.

위코드는 #include<openssl/hmac,h> 를 사용하는 코드로써 
visual stido 2022를 사용하시는 분들은
openssl 를 다운받아 visual stdio 2022 에 적용을 시켜줘야합니다.

https://slproweb.com/products/Win32OpenSSL.html 위 사이트에서 openssl를 다운 받아줍니다.
VC++ 디렉터리에 아래와 같이 적용시켜줍니다.
포함 디렉터리에 다운받은 Openssl #include 파일을 적용시켜줍니다.
라이브러리 디렉토리에 openssl의  \lib 파일과 \lib\VC 파일을 적용시켜줍니다.

링커에 입력에서도 다음과 같이 적용시켜줘야합니다.
링커의 입력에서 추가 종속성을 편집합니다.

다음은 명령프로롬트를 관리자 권한으로 실행시켜줍니다. 
cd C:\Program Files\OpenSSL-Win64\lib\VC 디렉토리로 이동 
dir VC /b /a-d | findstr /v /i ".def$" & dir /b /a-d | findstr /v /i ".def$" 사용하여 나온 결과를 복사 하여 
추가 종속성에 붙여넣기 해줍니다.

마찬가지로 cd C:\Program Files\OpenSSL-Win64\lib 디렉토리로 이동
dir VC /b /a-d | findstr /v /i ".def$" & dir /b /a-d | findstr /v /i ".def$" cmd에 사용하여 나온 결과를 복사하여 
추가 종속성에 붙여넣어줍니다.

visual stido 2022 버전에서 openssl을 적용을 완료 시켰습니다.

다음 TOTP.cpp를 사용하여 실행시켜주면 아래와 같은 결과값이 나옵니다.



## execution result

![image](https://github.com/SC-Han/Totp/assets/144402856/fb34c636-1986-48bd-946d-fb483dfde5ea)
