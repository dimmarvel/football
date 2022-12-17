build : _build
	cd $< && cmake .. && make -j9

run_app :
	cd _build/football && ./fbserver

run_tests :
	cd _build/tests && ./fbtests

_build :
	mkdir _build


