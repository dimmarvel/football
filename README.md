# Football APP

 Footbal - application for football trainers, to work with a database of students, tracking their progress in the format of grades.

---

# Build

Init submodule:

`git submodule update --init --recursive`

Run make Makefile for build:

```
make build          - cmake and make
make run_server     - run server
make run_client     - run client
make run_tests      - run tests
```

# Libs
App libs:
- config - app settings handler lib;
- core - core functional, redis wrapper, etc;
- database - light weight wrapper on redis;
- rpc - client for communication with server;
- server - nesting server;
- storage - for storing and retrieving data;
Another libs:
- tests - use gtest lib;

Third party libraries:
- spdlog;
- yas;
- hiredis && redis-plus-plus

# Run example

![readme_jpeg/run.jpeg](./readme_jpeg/run.jpeg)
