
DESCRIPTION
===========

The Phorward Toolkit provides a powerful set of useful functions for C programmers, which heavily focus on the topic of compiler-frontend development, meaning parsing and lexical analysis. The project can be seen as a dynamic generator and executor for lexers and parsers which can be defined and executed immediatelly within the program's sourcecode, making an extra step of generating parse tables or a recursive-descent parser unnecessary.

The following example defines a simple grammar, runs a parser and prints the generated abstract syntax tree:

    #include <phorward.h>
    
    int main()
    {
        pparse* p;
        parray* a;
        char*   s = "1+2*(3+4)+5";
        char*   e;
    
        p = pp_create( 0,
    			"%emitall"
    			"f: /[0-9]+/ | '(' e ')';"
    			"t: t '*' f | f ;"
    			"e: e '+' t | t ;" );
    
        if( !pp_parse_to_ast( &a, p, s, &e ) )
            return 1; /* parse error */
    
        pp_ast_print( a );
        return 0;
    }

(to compile it, run: gcc -o example example.c -lphorward)

Additionally, the toolkit also provides useful general-purpose extensions for dynamic data structures (linked lists, hash-tables, stacks and arrays), extended string management functions and some platform-independent, system-specific helper functions.


FEATURES
========

The Phorward Toolkit provides

- Parser development tools
    - BNF-based grammar definition
    - generators and executors for LR, LALR and LL grammars
    - a uniform AST (abstract syntax tree) representation
    - tools for AST traversal (coming soon!)
    - tools for parser deployment (coming soon!)
- Lexer development tools
    - regular expressions and pattern definition interface
    - plex for lexical analyzers
    - pregex for regular expressions
    - tools for regex and lexer deployment
    - string functions for regular expression matching, splitting and replacement
- Dynamic data structures
    - plist for linked-lists with build-in hash table support,
    - parray for arrays and stacks.
- Extended string management functions
    - concat, extend, tokenize, shorthand allocation of strings and wide-character strings
    - consistent byte- and wide-character (unicode) function support
    - unicode support for UTF-8 in byte-character functions
- Debug und trace facilities
- A build-in DOM-based XML-parser
- Universal system-specific functions for platform-independent C software development
    - Unix-style command-line parser
    - Mapping files to strings
- Object-oriented fashion for all function interfaces (e.g. plist, parray, pregex, pgram, ...)
- Growing code-base of more and more powerful functions

Please check out http://phorward.phorward-software.com/ from time to time to get the latest news, documentation, updates and support on the Phorward Toolkit.


BUILDING
========

Building the Phorward Toolkit is simple as every GNU-style open source program. Extract the release tarball or clone the Mercurial repository into a directory of your choice.

Then, run

    ./configure

to configure the build-system and generate the Makefiles for your current platform. After successful configuration, run

    make

and

    make install

(properly as root), to install the toolkit into your system.

On Windows systems, the usage of http://cygwin.org/ or another Unix shell environment is required. The Phorward Toolkit also perfectly cross-compiles on Linux using the MinGW and MinGW_x86-64 compilers.

To compile into 32-Bit Windows executables, configure with

    ./configure --host=i486-mingw32 --prefix=/usr/i486-mingw32

To compile into 64-Bit Windows executables, configure with

    ./configure --host=x86_64-w64-mingw32 --prefix=/usr/x86_64-w64-mingw32


LOCAL DEVELOPMENT BUILD-SYSTEM
==============================

Alternatively to the autotools build system used for installation, there is also a simpler method on setting up a local build system for development and testing purposes.

Once, type

    make -f Makefile.gnu make_install

then, a simple run of

    make

can be used to simply build the entire library or parts of it.

Note, that changes to the build system then must be done in the local Makefile, the local Makefile.gnu as well as the Makefile.am for the autotools-based build system.


AUTHOR
======

The Phorward Toolkit is developed and maintained by Jan Max Meyer, Phorward Software Technologies.

It is the result of a several years experience in parser development systems, and has been preceded by the parser generators UniCC (http://unicc.phorward-software.com/) and JS/CC (http://jscc.phorward-software.com), and shall be the final step for an ultimate, powerful compiler-frontend toolchain.

Help of any kind to extend and improve this product is always appreciated.


LICENSE
=======

This product is an open source software released under the terms and conditions of the 3-clause BSD license.


COPYRIGHT
=========

Copyright (C) 2006-2015 by Phorward Software Technologies, Jan Max Meyer.

You may use, modify and distribute this software under the terms and conditions of the 3-clause BSD license. The full license terms can be obtained from the file LICENSE.

THIS SOFTWARE IS PROVIDED BY JAN MAX MEYER (PHORWARD SOFTWARE TECHNOLOGIES) AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL JAN MAX MEYER (PHORWARD SOFTWARE TECHNOLOGIES) BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
