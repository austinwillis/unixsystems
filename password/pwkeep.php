<?php
/*Austin Willis
Password Keeper
CS 375*/
$handle = fopen ("php://stdin","r");
$user = get_current_user();
$password;

function help() {
    echo "\nOptions:\nh : print this information\na : add site record\no : open a url\nr : replace site record\nd : delete site record\ns : search all entries for a string\nl : list site records\ne : export user records\ni : import user records\nq : quit\n\nEnter an option: ";
}

function userinput() {
    global $handle, $user;
    $option = 1;
    echo "Succesfully logged in.\n";
    echo "Enter h for help.\n";
    while ($option != "q\n") {
        echo "Enter an option: ";
        $option = fgets($handle);
        if ($option == "a\n")
            newsite();
        if ($option == "h\n")
            help();
        if ($option == "l\n")
            listsite();
        if ($option == "o\n")
            openurl();
        if ($option == "d\n")
            deleteurl();
        if ($option == "r\n")
            replaceurl();
        if ($option == "s\n")
            search();
        if ($option == "e\n")
            export();
        if ($option == "i\n")
            import();
  }
}

function export() {
    global $handle, $user, $password;
    $continue = true;
    $iv = substr(md5('iv'.$password, true), 0, 8);
    $key = substr(md5('pass1'.$password, true) .
    md5('pass2'.$password, true), 0, 24);
    $opts = array('iv'=>$iv, 'key'=>$key);
    $fi = new FilesystemIterator(".pwkeep/.$user", FilesystemIterator::SKIP_DOTS);
    echo "Enter a filename for the export file: ";
    $line = fgets($handle);
    $filename = trim(preg_replace('/\s\s+/', ' ', $line)); 
    if (file_exists($filename)) {
	echo "There is already an export with that name. Would you like to replace it. (y/n): ";
	$line = fgets($handle);
	strtolower($line);
	if ($line == "y\n") {
	    $continue = true;
	    unlink($filename);
        } else {
	    $continue = false;
        }
    }
    if ($continue) {
    $file = fopen($filename, 'wb');
    $files = iterator_count($fi);
    fwrite($file, "PWTEXT $files\n");
    if ($dir = opendir(".pwkeep/.$user")) {
        while (false !== ($entry = readdir($dir))) {
            if ($entry != "." && $entry != "..") {
		$entryfile = fopen(".pwkeep/.$user/$entry", 'rb');
                stream_filter_append($entryfile, "string.rot13", STREAM_FILTER_READ, $opts);
		fwrite($file, "\n");
	        for ($i = 0; $i < 4; $i++) {
		    $line = fgets($entryfile);
		    if ($i == 0)
			fwrite($file, "url=");
		    if ($i == 1)
			fwrite($file, "userid=");
		    if ($i == 2)
			fwrite($file, "passwd=");
		    if ($i == 3)
			fwrite($file, "comment=");
		    fwrite($file, $line);
		}
		fclose($entryfile);
	    }	
        }
    }
    fclose($file);
    closedir($dir);
    }
}

function import() {
    global $password, $user, $handle;
    echo "Enter the filename of the record you would like to import: ";
    $line = fgets($handle);
    trim($line);
    $line = trim(preg_replace('/\s\s+/', ' ', $line));
    if (file_exists($line)) {
	$file = fopen($line, 'rb');
     	$line = fgets($file);
        $parts = explode(' ', $line);
        $records = $parts[1];
        $line = fgets($file);
        for ($i = 0; $i < $records; $i++) {
 	    $line = fgets($file);
	    $linepart = explode('=', $line);
            $urlpart = explode('.', $linepart[1]);
	    $iv = substr(md5('iv'.$password, true), 0, 8);
   	    $key = substr(md5('pass1'.$password, true) .
    	    md5('pass2'.$password, true), 0, 24);
    	    $opts = array('iv'=>$iv, 'key'=>$key);
	    $location = ".pwkeep/.$user/$urlpart[0].txt";
	    if (file_exists($location)) {
		unlink($location);
 	    }
            $site = fopen(".pwkeep/.$user/$urlpart[0].txt", 'wb');
            stream_filter_append($site, "string.rot13", STREAM_FILTER_WRITE, $opts);
	    fwrite($site, $linepart[1]);
	    for ($j = 0; $j < 3; $j++) {
		$line = fgets($file);
		$linepart = explode('=', $line);
		fwrite($site, $linepart[1]);
	    }
	    if ($i != $records - 1)
	        $line = fgets($file);
        }
    } else {
	echo "Unable to find file.\n";
    }
}

function deleteurl() {
    global $handle, $user;
    echo "Enter the url you would like to delete: ";
    $line = fgets($handle);
    $domain_parts = explode('.', $line);
    $site =  ".pwkeep/.$user/$domain_parts[0].txt";
    if (file_exists($site)) {
  	unlink($site);  
	echo "Deleted $site.\n";
    } else {
	echo "A record for that site could not be found.";
    }
}

function replaceurl() {
    global $handle, $user;
    echo "Enter the url you would like to replace: ";
    $line = fgets($handle);
    $domain_parts = explode('.', $line);
    $site =  ".pwkeep/.$user/$domain_parts[0].txt";
    if (file_exists($site)) {
  	unlink($site);  
	echo "Replacing $site.\n";
        newsite();
    } else {
	echo "Record could not be replaced. File not found.\n";
    }
}

function openurl() {
    global $handle, $password, $user;
    $iv = substr(md5('iv'.$password, true), 0, 8);
    $key = substr(md5('pass1'.$password, true) .
    md5('pass2'.$password, true), 0, 24);
    $opts = array('iv'=>$iv, 'key'=>$key);
    echo "Enter the url you would like to open: ";
    $line = fgets($handle);
    $domain_parts = explode('.', $line);
    $url =  ".pwkeep/.$user/$domain_parts[0].txt";
    if (file_exists($url)) {
	$iv = substr(md5('iv'.$password, true), 0, 8);
   	$key = substr(md5('pass1'.$password, true) .
    	md5('pass2'.$password, true), 0, 24);
    	$opts = array('iv'=>$iv, 'key'=>$key);
    	$file = fopen($url, 'rb');
    	stream_filter_append($file, "string.rot13", STREAM_FILTER_READ, $opts);
	echo "\n";
        for ($i = 0; $i < 4; $i++) {
            $line = fgets($file);
            if ($i == 0)
		echo "URL: ";
	    if ($i == 1)
		echo "Username: ";
            if ($i == 2)
		echo "Password: ";
            if ($i == 3)
		echo "Comment: ";
            echo $line;
        } 
	echo "\n";
	fclose($file);
    } else {
        echo "There is no record for that site.\n";
    }
}

function newsite() {
    global $handle, $user, $password;
    echo "Enter the url for the site: ";
    $line = fgets($handle);
    $domain_parts = explode('.', $line);
    $iv = substr(md5('iv'.$password, true), 0, 8);
    $key = substr(md5('pass1'.$password, true) .
    md5('pass2'.$password, true), 0, 24);
    $opts = array('iv'=>$iv, 'key'=>$key);
    if (file_exists(".pwkeep/.$user/$domain_parts[0].txt")) {
        echo "There is already a record for this site. Use the r option if you would like to replace it.\n";
    } else {
        $file = fopen(".pwkeep/.$user/$domain_parts[0].txt", 'wb');
        stream_filter_append($file, "string.rot13", STREAM_FILTER_WRITE, $opts);

        fwrite($file, $line);
        echo "Enter your user id for this site: ";
        $line = fgets($handle);
        fwrite($file, $line);
        echo "Enter your password for this site: ";
        $line = fgets($handle);
        fwrite($file, $line);
        echo "Enter a comment for this site: ";
        $line = fgets($handle);
        fwrite($file, $line);
        fclose($file);
    }
}

function listsite() {
    echo "\nSite logs for this user: \n";
    global $user;
    if ($dir = opendir(".pwkeep/.$user")) {

    while (false !== ($entry = readdir($dir))) {

        if ($entry != "." && $entry != "..") {

            echo "$entry\n";
        }
    }

    closedir($dir);
    }
    echo "\n";
}

function search() {
    global $user, $handle;
    echo "Enter the term you would like to search for: ";
    $line = fgets($handle);
    echo "\nFound the term in these records: \n";
    if ($dir = opendir(".pwkeep/.$user")) {

    while (false !== ($entry = readdir($dir))) {

        if ($entry != "." && $entry != "..") {
	    searchfile($entry, $line);
        }
    }

    closedir($dir);
    }
    echo "\n";
}

function searchfile($entry, $line) {
    global $password, $user;
    $found = false;
    $iv = substr(md5('iv'.$password, true), 0, 8);
    $key = substr(md5('pass1'.$password, true) .
    md5('pass2'.$password, true), 0, 24);
    $opts = array('iv'=>$iv, 'key'=>$key);
    $file = fopen(".pwkeep/.$user/$entry", 'rb');
    stream_filter_append($file, "string.rot13", STREAM_FILTER_READ, $opts);
    for ($i = 0; $i < 4; $i++) {
        $line2 = fgets($file);
        if (strcmp($line2,$line) == 0) {
            $found = true;
        }
    }
    if ($found == true)
        echo "$entry\n";
}

echo "Welcome $user.\n";
if (!file_exists('.pwkeep')) {
    mkdir('.pwkeep', 0777, true);
}
if (!file_exists(".pwkeep/.$user")) {
    mkdir(".pwkeep/.$user", 0777, true);
}
if (!file_exists(".pwkeep/$user.txt")) {
    $hash = 's';
    $hash2 = 'a';
        while ($hash != $hash2) {
        echo "Set a password for this user: ";
        $password = fgets($handle);
        $hash = hash('ripemd160', $password);
        echo "Confirm password: ";
        $password = fgets($handle);
        $hash2 = hash('ripemd160', $password);
        if ($hash != $hash2)
            echo "Passwords do not match. Try again.\n";
    }
    file_put_contents(".pwkeep/$user.txt", $hash2);
    userinput();
} else {
    $line = 1;
    $hash = 2;
    while ($hash != $line) {
        $userfile = fopen(".pwkeep/$user.txt", 'r');
        $line = fgets($userfile);
        echo "Enter your password: ";
        $password = fgets($handle);
        $hash = hash('ripemd160', $password);
        if ($hash != $line) {
            echo "Password incorrect. Try again.\n";
        }
    }
    userinput();
}
?>
