
#
# To start with ATMOS:
# 1) Read README
# 2) for the code, cd src/ and look into the Makefile there.
# 2) for the documentation, run 'make docs' here
#

all:
	(cd src ; make)
	make docs

docs:
	(cd doxygen ; doxygen atmos.cnf ; cd latex ; make ; make refman.ps)

all-emu:
	(cd src ; make -f Makefile.emu)
	(cd doxygen ; doxygen atmos.cnf ; cd latex ; make ; make refman.ps)

clean:
	(cd src ; make clean)
	(cd doxygen ; rm -rf html latex)

clean-emu:
	(cd src ; make -f Makefile.emu clean)
	(cd doxygen ; rm -rf html latex)

