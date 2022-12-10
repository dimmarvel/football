build : _build
	cd $< && cmake .. && make -j9

run :
	cd _build/football && ./fbserver

_build :
	mkdir _build


