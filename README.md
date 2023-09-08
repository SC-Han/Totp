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

## execution result

![image](https://github.com/SC-Han/Totp/assets/144402856/fb34c636-1986-48bd-946d-fb483dfde5ea)
