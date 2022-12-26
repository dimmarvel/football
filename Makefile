build : _build
	cd $< && cmake -Dgtest_build_samples=ON -DCMAKE_BUILD_TYPE=Debug .. && make -j9

run_app :
	cd _build/football && ./fbserver

run_tests :
	cd _build/tests && ./fbtests

_build :
	mkdir _build


