```bash
# 다중 파이프 테스트
./pipex infile "ls -l" cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat "grep -v pipex" outfile

# 병렬 처리 테스트
time ./pipex infile "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" outfile

# open 에러 테스트
touch infile outfile permission_denied && chmod 000 permission_denied

./pipex permission_denied "ls -l" "grep pipex" outfile
./pipex permission_denied "ls -l" cat cat "grep pipex" outfile
./pipex infile "ls -l" "grep pipex" permission_denied
./pipex infile "ls -l" cat cat "grep pipex" permission_denied
./pipex none "ls -l" "grep pipex" outfile
./pipex none "ls -l" cat cat "grep pipex" outfile

# 올바르지 않은 명령어 테스트
./pipex infile a b outfile

# 시스템콜 에러 테스트
ulimit -a
ulimit -u 400; ./pipex infile "ls -l" cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat "grep -v pipex" outfile
ulimit -n 10; ./pipex infile "ls -l" cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat cat "grep -v pipex" outfile

# here_doc 테스트
./pipex here_doc limiter cat cat outfile

# /dev/random
./pipex /dev/random "head -c 100" "wc -c" outfile

# zombie process 테스트
./pipex infile ls "sleep 5" ls "sleep 5" ls "sleep 5" ls "sleep 5" ls "sleep 5" outfile
ps

# unset PATH 테스트
unset PATH; ./pipex infile "ls -l" cat outfile
```
