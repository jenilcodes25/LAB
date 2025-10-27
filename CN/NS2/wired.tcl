set udp [new Agent/UDP]
set null [new Agent/Null]
$ns attach-agent $n0 $udp
$ns attach-agent $n4 $null
$ns connect $udp $null

set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]
$ns attach-agent $n1 $tcp
$ns attach-agent $n5 $sink
$ns connect $tcp $sink

#===================================
#        Applications Definition        
#===================================
#Setup a FTP Application over UDP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp

#Setup a CBR Application over TCP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

$ns at 1.0 "$cbr start"
$ns at 2.0 "$ftp start"
set finish "finish"
$ns at 10.0 "$finish"
