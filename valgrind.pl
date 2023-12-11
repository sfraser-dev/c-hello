# usage: perl valgrind.pl program.exe

use strict;
use warnings;
use feature qw / say /;
use Data::Dumper;

# need to compile .exe WITHOUT any sanitizer info to use valgrind.
# guess they don't play well together

# get the filenames
my $num_args  = $#ARGV + 1;
my $fullpath  = __FILE__;
my @splitter  = split( "/", $fullpath );
my $perl_file = $splitter[-1];
( my $log_file = $perl_file ) =~ s/\.pl$/\.log/;
my $c_exe = $ARGV[-1];

# execute valgrind command
if ( $num_args != 1 ) {
    print "\nError. Usage is $perl_file program.exe\n";
    exit;
}
else {
    my $terminal_output =
      qx(valgrind --log-file=$log_file -v --leak-check=full ./$c_exe);
    say $terminal_output;
}

# print the last lines of log file to terminal (tail)
my @lines;
open my $fh, '<', $log_file or die "Couldn't open file: $!";
while (<$fh>) {
    push( @lines, $_ );
}
close $fh;
for ( -15 .. -1 ) {
    print $lines[$_];
}
