build : _build
	cd $< && cmake -Dgtest_build_samples=ON -DCMAKE_BUILD_TYPE=Debug .. && make -j9

run_server :
	cd _build/football && ./server/fbserver

run_client :
	cd _build/football && ./client/fbclient

run_tests :
	cd _build/tests && ./fbtests

clear :
	cd .. && chown -R dmatsiukhov football/

_build :
	mkdir _build


