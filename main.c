#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> //needed for chdir()

static char * concat(const char * s1, const char * s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char * result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    if(result == NULL) {
      fprintf(stderr, "Out of memory, exiting\n");
      exit(1);
       }   
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
}

int main() {
 puts("Specify with a number what is that you want to do.");
 puts("1. Get the list of commands with \033[3mhelp\033[0m .");
 puts("2. Get information on the command of your choice with \033[3mhelp command_of_your_choice\033[0m .");
 puts("3. Show information about this node \033[3mgetinfo\033[0m, \033[3mlistchannels\033[0m, \033[3mlistfunds\033[0m .");
 puts("4. Connect to another lightning node with \033[3mconnect\033[0m or \033[3mbootstrap-node.sh\033[0m .");
 puts("5. Shutdown your c-lightning node .");
 puts("8. Payments: \033[3mdecode\033[0m, \033[3mgetroute\033[0m, \033[3mkeysend\033[0m, \033[3mpay\033[0m, \033[3mwithdraw\033[0m .");
 puts("9. Generate a new address with \033[3mnewaddr\033[0m .");


 int choice;
 
 choice = getchar();
 
 
 if ( choice == '1' ) {
 
 system("lightning-cli help");
 
  exit(0);
  }
 else if ( choice == '2' ) {
  while (getchar() != '\n');
  puts("Whats is the command that you want to read about?");
  char command[40]; 
  fgets(command, 40, stdin);
  command[strcspn(command, "\n")] = 0;    
  char * help_command = concat("lightning-cli help ", command);
  system(help_command);
  free(help_command); 
  exit(0);
    }  
 else if ( choice == '3' ) {
   while (getchar() != '\n');
   puts("Specify with a number what is that you want to do.");
   puts("1. Show information about this node: \033[3mgetinfo\033[0m .");
   puts("2. Get data on all lightning nodes have open channels with this node with \033[3mlistpeers\033[0m .");
   puts("3. View all funds available, either in UTXOs, wtih their addresses, in the internal wallet or funds locked in channels. \033[3mlistfunds\033[0m .");
   choice = getchar();
      
   if ( choice == '1' ) {
   system("lightning-cli getinfo");
   exit(0);
      }
   else if ( choice == '2' ) {
   system("lightning-cli listpeers");//my testnet pubkey
   exit(0);
      }
   else if ( choice == '3' ) {
      system("lightning-cli listfunds");
      exit(0);
  
       }
     } 
     
 else if ( choice == '4' ) {
   while (getchar() != '\n');
     puts("What is the node's ID? Optionally follow with address and port separated from each other by whitespace.");
     char pubkey[98]; //The pubkey seems to have 66 characters, but let us add some more for the optional address and port
     fgets(pubkey, 98, stdin);
     pubkey[strcspn(pubkey, "\n")] = 0;
     char * ccommand1 = concat("lightning-cli connect ", pubkey);
     
     //system("lightning-cli connect 03864ef025fde8fb587d989186ce6a4a186895ee44a926bfc370e2c366597a3f8f");//the top capacity mainnet node as of 9/2021
     system(ccommand1);//one of the top capacity testnet node as of 9/2021
     free(ccommand1);//system("lightning-cli connect 030f0bf260acdbd3edcad84d7588ec7c5df4711e87e6a23016f989b8d3a4147230@163.172.94.64:9735");//one of the top capacity testnet node as of 9/2021
     exit(0);
      }
   
  
  else if ( choice == '5' ) {
    system("lightning-cli stop");
    exit(0);
   } 
  
 
  else if ( choice == '8' ) {
    while (getchar() != '\n');
    puts("Specify with a number what is that you want to do.");
    puts("1. Decode the invoice with \033[3mdecodepay\033[0m .");
    puts("2. See how much fees you would pay with \033[3mgetroute\033[0m and the risk factor of 10 .");
    puts("3. Pay with \033[3mkeysend\033[0m .");
    puts("4. Pay with \033[3mpay\033[0m .");
    puts("5. Send onchain with \033[3mwithdraw\033[0m .");
    choice = getchar();
   if ( choice == '1' ) {
    while (getchar() != '\n');
    puts("Give me the bolt11_invoice?");
    char invoice[400]; 
    fgets(invoice, 400, stdin);
    invoice[strcspn(invoice, "\n")] = 0;
    char * decode = concat("lightning-cli decodepay ", invoice);
    system(decode);
    free(decode); 
    exit(0);
    }  
   else if ( choice == '2' ) {
    while (getchar() != '\n');
    puts("What is the node's ID?");
    char pubkey[68]; //The pukey seems to have 66 characters
    fgets(pubkey, 68, stdin);
    pubkey[strcspn(pubkey, "\n")] = 0;
    char * getroute_command1 = concat("lightning-cli getroute ", pubkey);
    free(getroute_command1);
    char * getroute_command2 = concat(getroute_command1, " ");
    puts("What is the amount in sats?");
    char amount[12]; //The pubkey seems to have 66 characters
    fgets(amount, 12, stdin);
    amount [strcspn(amount, "\n")] = 0;
    char * getroute_command3 = concat(getroute_command2, amount);
    free(getroute_command2);
    char * getroute_command4 = concat(getroute_command3, "000 10");
    free(getroute_command3);
    system(getroute_command4);
    free(getroute_command4);
    exit(0);
    } 
  else if ( choice == '3' ) {
    while (getchar() != '\n');
    puts("What is the node's ID?");
    char pubkey[68]; //The pukey seems to have 66 characters
    fgets(pubkey, 68, stdin);
    pubkey[strcspn(pubkey, "\n")] = 0;
    char * keysend_command1 = concat("lightning-cli keysend ", pubkey);
    free(keysend_command1);
    char * keysend_command2 = concat(keysend_command1, " ");
    puts("What is the amount in sats?");
    char amount[12]; //The pubkey seems to have 66 characters
    fgets(amount, 12, stdin);
    amount [strcspn(amount, "\n")] = 0;
    char * keysend_command3 = concat(keysend_command2, amount);
    free(keysend_command2);
    char * keysend_command4 = concat(keysend_command3, "000");
    free(keysend_command3);
    system(keysend_command4);
    free(keysend_command4);
    exit(0);
    } 
  else if ( choice == '4' ) {
    while (getchar() != '\n');
     
    puts("Give me the bolt11_invoice?");
    char invoice[400]; 
    fgets(invoice, 400, stdin);
    invoice[strcspn(invoice, "\n")] = 0;
    char * invoice_pay = concat("lightning-cli pay ", invoice);
    system(invoice_pay);
    free(invoice_pay); 
    exit(0);
    } 
  else if ( choice == '5' ) {
      while (getchar() != '\n');
        puts("Destination?");
        char d[44]; 
        fgets(d, 44, stdin);
        d[strcspn(d, "\n")] = 0;
        puts("The amount to be sent in satoshis? \033[3mall\033[0m if the entire balance");
        char a[15];
        fgets(a, 15, stdin);
        a[strcspn(a, "\n")] = 0;
        char * c1 = concat("lightning-cli withdraw ", d);
        char * c2 = concat(c1, " ");
        free(c1);
        char * c3 = concat(c2, a);
        free(c2);
        char * c4 = concat(c3, " slow");
        free(c3);
        system(c4);
        puts(c4);
        free(c4); 
        exit(0);
    }
  }
  else if ( choice == '9' ) {
    system("lightning-cli newaddr");
    exit(0);
   }
   
   

   
return 0;	
}
/***********************************************************************
alias bcliTc='cd ~/.bitcoin/testnet3  && ~/CS/SoftwareDevelopment/MySoftware/C/bcli-testnet/a.out'
Ctrl-H, replace ' -testnet' with '' to apply the code to apply to bcli on the mainnet

alias bcliTc='cd ~/.bitcoin/testnet3  && ~/CS/SoftwareDevelopment/MySoftware/C/bcli-testnet/a.out'
Ctrl-H, replace ' -testnet' with '' to apply the code to apply to bcli on the mainnet

https://bitcoin.stackexchange.com/questions/107930/what-are-the-minimum-and-maximum-lengths-of-a-lightning-invoice-address
https://1ml.com/node?order=capacity
https://1ml.com/testnet/node?order=capacity
https://bitcoin.stackexchange.com/questions/81349/lightning-cli-list-only-my-channels
*****************************************************************/
