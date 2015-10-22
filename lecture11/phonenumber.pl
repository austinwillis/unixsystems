#!/usr/bin/perl
$number = $ARGV[0];
print $number;

if ($number =~ /(\+*\d{1,})*([ |\(])*(\d{3})[^\d]*(\d{3})[^\d]*(\d{4})/) {
  print " is a valid phone number\n";
} else {
  print " is not a valid phone number\n";
}
