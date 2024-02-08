## CS50 TSE Crawler
# Sam Rothschild, CS50 TSE

# Implementation
The crawler.c file is implemented with a main function which parses the arguments parsed into it. Initially it checks that the correct number of arguments (3) are entered, and it then checks each of them individually. First it checks that the seedURL can be normalized, and then checks it is internal. If these tests are met it then checks that the page directory supplied (the location where we want to write our data) exists and is writeable. Finally, it checks that the max depth (how deep into webpages we will allow our crawler to go) is a positive integer. If all these checks are met, then the crawler function is run using the argument and it returns 0 to indicate no error.

The crawler function creates new bag and hashtable structures. The bag stores the webpages to visit and the hashtable stores sites we have already visited. Then, while the list of websites to visit (ie the bag) isn't empty, we extract a page (and add in an artificial pause as per politeness instructions in the spec) and if it is possible to save it then we get the html and save it. We then increment the id number of the page for storage in the page directory. We then run a check that the current depth does not exceed the max depth provided by the user -- if it does then we return false and stop. If we have more depth to go then we get the next URL and normalize it. After this we create a new webpage for each of the webpages on the current one and add them to our bag of pages to visit. We then return true to indivate the process is finished.

The page fetcher function leverages the existing webpage fetch method provided and simply returns its result.

The page saver function outputs a file given an integer name by the crawler fucntion to the pagedir directory, this is how we can access the data resulting from our crawling.

The page scanner function goes through a webpage getting all its embedded URLs. It parses them by normalising them and checking that they are internal. It then creates a webpage for them and inserts that in the bag of pages to visit. It does a check to ensure that the webpage isn't already in the hashtable of websites seen.

