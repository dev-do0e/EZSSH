==========================================================
DISSH 동작 방식

1. DISSH_SETTING_JSON_PARSING에서 lampadx가 연결되어 있는 lampad의 정보를 가지고 온다.

2. 1번에서 가지고 온 lampad의 정보를 토대로 lampad에 Rest api를 호출하여 lampad에 연결되어 있는 lampadx의 정보를 가지고 온다.

3. 가지고 온 lampadx의 정보를 response_post_json에 저장한다.

4. response_post_json에 저장되어 있는 정보를 토대로 lampadx에 접근하여 cage와 Faklient를 변경한다.

5. 완료

==========================
DISSH 동작 방식 개선안

**
json parsing하는 class 하나로 묶기
**

1. dissh.json에서 lampad와 lampadx의 정보를 가져옴 (구조체 사용)

2. 가져온 lampad 정보로 lampad 서버에 post 요청하여 Civet7token값 가져오기

3. Civet7token 값으로 다시 lampad에 get 요청해서 lampad에 /q/paradox 요청

4. /q/paradox로 가져온 json에 reponsive가 true인 애들 필터링 후 ip 저장

5. 저장된 ip를 기반으로 libssh 실행

===========================================================
개발 시 중요하게 여겨야 하는 사항

Rest api의 Request를 get과 post로 나누어서 구현함

workspace를 카피해서 사용한다면
1. .vscode의 task.json, launch.json 파일을 변경하기
2. cmakecache.txt를 삭제하기

빌드했는데 가끔 CMakeFiles만 생성되면 CMakeLists.txt을 잘 고쳐봐라 (버전 명시)

일반적으로 실행헀을 때 아무 오류 내용 없이 실행에 실패헀을 때 debug 경로에 exe를 직접 실행해보기(GUI로)

LNK2019 오류
코드 안에 쓰인 함수나 변수가 다른 파일에 있는데 그 파일이 빌드 과정속에 없다라고 하는 것
cmake 확인

Rest API 호출이 끝나면 무조건
curl_easy_cleanup(curl);
해야 한다

안하면 쿠키 값이 안들어오든, 호출이 안되든 한다 무조건 해라

주석 변경사항 확인하는 지 체크해볼거임