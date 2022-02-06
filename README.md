# minishell

#### 01/02

(seyun)
1. 파싱트리를 사용하기 위해 토큰 나누기 시작.
2. 환경변수 목록을 리스트에 저장하기 get_env()  new_list // lstadd_back 과정에서 t_list형식과 t_env 충돌 02/02 오전 수정 예정

#### 02/02

(seyun)

1. t_list *env  lstadd_back 수정완료

#### 06/02

1. (ing)line 을 space 단위로 나눠서 token의 개수를 확인 (quote인 경우 "/' 가 닫혀있는지 확인)
2. (예정)token을 각각의 type으로 정의 | 파이프 > < >> << 리다이렉션 cmd 로 분류 
