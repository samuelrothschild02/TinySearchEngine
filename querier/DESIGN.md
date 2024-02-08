## CS50 TSE Querier
# Sam Rothschild, CS50 TSE

# Querier high level design:
Parse arguments passed in to ensure they are legitimate: check that there are 2 arguments, that the page directory provided is a valid crawler directory and lastly that the file provided can be written to. If so, and only then, do we pass the arguments to querier to run. We then tokenize the input, checking for invalid characters etc. We also take into account the key words 'and' and 'or' when creating our search. We then find a union (if necessary in the countersets) and print the appropriate output from highest-scoring (where priority is indicated by how many times a given word appears) to lowest-scoring.

# What is the querier and how does it do its job:
The querier uses the index data structure developed in the previous lab and counters to rank the query results according to the hierarchy in the lab spec.

The querier tokenizes the input into individual words, ignoring blank lines and returning an error if a special character of any sort or number is inputted. Once the input is tokenized and normalized we then use the clean input to set around the actual querying: assigning score and ranking. 
