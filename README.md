# arch2-2019-cw-LowIQ
This work was done as part of coursework following the specification: https://github.com/m8pple/arch2-2019-cw

The following commands specify how to run the testbench:
<pre>
make simulator
</pre>
makes a simulator exectutable file inside the ./bin folder
<pre>
make parser
</pre>
makes a parser executable in ./parser/bin/parser
<pre>
chmod u+x ./parser/bin/parser
</pre>
(in order to grant permission for the file)
<pre>
cd test
</pre>

<pre>
sh bingen.sh
</pre>
converts all the meta files in ./test/testcases into binary files
<pre>
cd ..
</pre>

<pre>
sh testbench.sh
</pre>
runs the binary files against the simulator and compares its results to expected values
