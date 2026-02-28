void crawl(const string& name, const string& indentation = "") {  
    cout << indentation << getTail(name) << endl;  

    if (isFile(name)) {
        // base case
        // nothing else to do
    } else if (isDirectory(name)) {
        // recursive case
        Vector<string> sublayer;
        listDirectory(name, sublayer);
        for (string entry : sublayer) {
            crawl(name + "/" + entry, indentation + "    "); 
        }
    }

    
}
