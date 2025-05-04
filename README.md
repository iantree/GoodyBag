# GoodyBag
This repository holds useful stuff that was encountered while rifling through the sock draw of some old code archives.
Each goody is either a standalone piece of code or code that is interdependent on other goodies.
To kick off this collection we have some case-insensitive versions of standard functions.

stristr -	is a case-insensitive version of strstr. This is a popular function and there are plenty of implementations
already in the public domain, with varying levels of competence. The one offered here is complete, adheres to the contract
for strstr and is an elegant and efficient implementation.

strichr -	this is a case-insensitive version of strchr. Although simple it is useful, underpinning the implementation
of stristr.

memichr -	Again simple providing a case-insensitive version of memchr.

memdump -	A simple memory dumping function.

More goodies to follow.
