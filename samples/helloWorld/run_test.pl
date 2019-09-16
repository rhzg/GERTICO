eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::Run_Test;

$status = 0;

$hA = new PerlACE::Process ("helloWorld", "A 1 100 > helloA.txt");
$hB = new PerlACE::Process ("helloWorld", "B 1 100 > helloB.txt");
$hC = new PerlACE::Process ("helloWorld", "C 1 100 > helloC.txt");

$hA->Spawn();
$hB->Spawn();
$hC->Spawn();

$clientA = $hA->WaitKill(1000);
$clientB = $hB->WaitKill(1000);
$clientC = $hC->WaitKill(1000);

if ($clientA != 0)
{
  print STDERR "helloWorld A failed $clientA\n";
  $status = 1;
}  

if ($clientB != 0)
{
  print STDERR "helloWorld B failed $clientB\n";
  $status = 1;
}  

if ($clientC != 0)
{
  print STDERR "helloWorld C failed $clientC\n";
  $status = 1;
}  

print STDERR "HelloWorld Test passed\n";
exit $status;
