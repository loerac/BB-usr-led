#!/usr/bin/perl

$PATH = "/sys/class/leds/beaglebone:green:usr";

sub writeLED {
	open(FILE, ">" .$PATH . $_[0] . $_[1]) or die "Couldn't open the file, $!";
	print FILE $_[2];
	close(FILE);
}

sub commands {
	if($_[0] == "1") {
		print "Turning usr". $_[1] ." ON\n";
		removeTrigger($_[1]);
		writeLED($_[1], "/brightness", "1");
	} elsif($_[0] == "2") {
		print "Turning usr". $_[1] ." OFF\n";
		removeTrigger($_[1]);
		writeLED($_[1], "/brightness", "0");
	} elsif($_[0] == "3") {
		print "Flashing usr". $_[1] . "\n";
		removeTrigger($_[1]);
		writeLED($_[1], "/trigger", "timer");
		writeLED($_[1], "/delay_on", "500");
		writeLED($_[1], "/delay_off", "500");
	} elsif($_[0] == "4") {
		open(DATA, "<" .$PATH . $_[1] . "/trigger");
		while(<DATA>) { print "$_"; }
		close(DATA);
	}
}

sub removeTrigger {
	writeLED($_[0], "/trigger", "none");
}

sub main() {
	print "\n====================================\n";
	print "Starting the LED Program\n";
	print "USER LED: usr0 [1], usr1 [2], usr2  [4], usr3   [8]\n";
	print "Commands: ON   [1], OFF  [2], FLASH [3], STATUS [4]\n";
	print "Exit: 0\n";
	print "====================================\n";
	print "Enter USER LED >> ";
	$bw = <>;

	while($bw != 0) {
		print "Enter command >> ";
		$cmd = <>;
		print "\n";
		
		if(($bw & 1) == 1) { commands($cmd, 0); }
		if(($bw & 2) == 2) { commands($cmd, 1); }
		if(($bw & 4) == 4) { commands($cmd, 2); }
		if(($bw & 8) == 8) { commands($cmd, 3); }
		print "\nEnter USER LED >> ";
		$bw = <>;
	}
	
	print "\n";
	for($i = 0; $i < 4; $i+=1) {
		removeTrigger($i);
		commands(2, $i);
	}
}

main();
