# minishell

ing - ing  
ok  - 완료  
x   - 예정  
??  - 모르겠는거...  

#### 01/02

(seyun)
1. (ok)파싱트리를 사용하기 위해 토큰 나누기 시작.
2. (ok)환경변수 목록을 리스트에 저장하기 get_env()  new_list // lstadd_back 과정에서 t_list형식과 t_env 충돌 02/02 오전 수정 예정

#### 02/02

(seyun)

1. (ok)t_list *env  lstadd_back 수정완료

#### 06/02

1. (ok)token split(space 단위로)  "/'일경우 "/'로 닫혀있는지 확인후 닫혀있지 않다면 -1 count 반환.
2. (?)" " // ' ' 안에 space 처리 (?????)
3. (x)나누어진 토큰 개수만큼 malloc후 token tpye  |  // >> << > < // cmd 로 나누어 정렬시키기.

#### 07/02

1. (ing)split_line 시작
2. $PATH // $? etc 적용안되는거 확인.

#### 08/02 

1. split_line 복붙 :/ 

#### 13/02

1. token.type까지 입력완료
