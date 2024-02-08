## CS50 TSE Crawler Testing.md
# Sam Rothschild, CS50 TSE crawler

# How to test + presentation of testing:
Attached in the crawler directory is a ./testing.sh file. Use 'make test' in order to run this. One example directory of what crawler output looks like is included. The majority of the tests are commented out so as not to overwhelm the user on first testing, in order to use each of the tests (described with a comment line), simply uncomment the line with the command on.

Important note: *It is important to have created a directory with the name of the third arg passed in to crawler BERFORE running ./crawler for the files to be put in this directory correctly*

# Test with incorrect command line arguments:
Test with incorrect number of arguments, URL that isn't internal, an invalid pagedir, and an incorrect maxDepth (ie not an int) to ensure that the parsing of arguments from the command line is working.

# Test with a seedURL that points to a non-existent server:
In this case test with a NULL argument.

# Test with a seedURL that points to a non-internal server:
In this case test with a non-internal argument.

# Test with a seedURL that points to a valid server but non-existent page:
Expect nothing to be written to file.

# Crawl a set of cross linked pages: 
Expect results to be written to directory correctly.

# Point crawler at a site and explore different depths:
Ensure that expected result tallies with outputted results: the depths are working correctly.

# Repeat different seedpage in the same site:
There should be some interesting starting points on different sites.

# Use depths 0, 1, and 2 on wikipedia playground:
Ensure that expected results tally with outputted results: the depths are working correctly.

# Test the crawler on the playground with a higher depth:
See results outputted. Be ready to kill it off if necessary.
