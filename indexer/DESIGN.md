## CS50 TSE Crawler
# Sam Rothschild, CS50 TSE

# Indexer high level design:
Parse arguments passed in to ensure they are legitimate: check that there are 2 arguments, that the page directory provided is a valid crawler directory and lastly that the file provided can be written to. If so, and only then, do we pass the arguments to indexer to run. We then build the index, save the index to a file and delete it when finished.

# What and how does the indexer do its job:
The indexer tracks words (of three characters or longer) -- specifically it tracks which files words appear in and how frequently they appear in each of those files. It was suggested in class that this will later be useful for the querier part of the search engine. The indexer operates using a hashtable approach where a given word is a key, and the item associated with that key is a counter set mapping a document ID to the number of times that word appears in the document. The design of hashtable makes it far quicker than just a regular set.
