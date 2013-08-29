/*										AUTHOR-JAYESH LAHORI(201101144)
 *									      	       OS ASSGN-2
 *				             1.)THE COMMENTS WRITTEN IN CENTER SPANNING THE WHOLE PAGE ARE COMMENTS WHICH ARE MEANT FOR EVALUATION
 *				             2.)PLEASE IGNORE SET OF COMMENTS WRITTEN IN BETWEEN, COZ THEY WERE USED FOR DEBUGGING
 *				             3.)ALL FN'S STARTING WITH EXEC ARE VARIOUS DIFF FN'S TO RUN USER DEFINED COMMANDS OF 1ST ASSIGNMENT WRITTEN AT LAST
 *				             4.)PIPING IS THE CONTROLLER FN TO CONTROL PIING OR PING + REDIRECTION OPERATPR COMBINATION
 *				             5.)REDIRECTOR FN HANDLES IF ONLY RE-DERICTION IS PRESENT WITH NO PIPING
 *				             6.)OTHER_C HANDLES OTHER COMMANDS WHICH ARE ALREADY DEFINED SYSTEM PROGRAMS LIKE GREP OR TO RUN EMACS,GEDIT, WC ETC,ETC
 *				             7.)BACKGROUND PROCESSES ARE ALSO RUN BY THE SAME FN
 *				             8.)ALL FUNCTIONS ARE QUITE VERBOSE WITH VARIABLES NAME & EXPLANOTORY ABOUT THE WORKING CAARIED OUT THEM
 *
 *				             						NOTE
 *1.)ALL COMMAND ENTERED BY USER SHOULD CONTAIN ATLEST 1 SPACE  BETWEEN EVERY INTERMEDIATE "WORD",ANY OTHER EXTRA WHITE SPACES @ START O COMMAND OR IN BETWWEN OR @LAST HAVE BEEN HANDLED
 *		             					AND HAVE BEEN IMPLEMENTED SO COZ THE TC'S SHOWN IN ASSGN WERE SO.
 *		             								:EG:
 *		             							   ls -al | wc -l            not ls-al|grep a
 *		             							   emacs &                   not emacs&
 *										   cat 2 > 4                 not cat 2>4
 *										
 */



#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>
#include<signal.h>
#include <fcntl.h>
#include <signal.h>
#include <wait.h>
void child_handler(int signum);
void sig_handler(int signum);
void getargs(char **array1,char *cmd,char *ip,char *op);
//void getargs(char **array1,char *cmd);
void print();
//void fpid();
//void cid();
void ctrlc_handler(int signum);
pid_t other_c(char* s);
void piping(char *s);
void stroking(char **parts,char *s);
void redirector(char * cmd);
void execpid();
void execpidall();
void execpidcurrent();
void exechist();
void exechistn(char command[]);
typedef struct stack
{
	char s[500];
	pid_t pid;
	int flag;
	int pip;
	int red;
}stack;
int top=-1;
stack st1[500];
char *buff2;
char dir[500];
char *array1[100];
int mflag=0;
int main()
{
	char c;
	signal(SIGCHLD, child_handler);
	signal(SIGINT,ctrlc_handler);
	char temp[500];
	char command[500];
	command[0]='\0';
	print();
	int i=0;
	buff2=dir;
	buff2=getcwd(buff2,100);
	//	printf("%s\n",dir);
	while(c!='\n')
	{
		scanf("%c",&c);
		if((c==' ' || c=='\t') && i==0)
			continue;
		if((c==' ' || c=='\t') && command[i-1]==' ')
			continue;
		else
			command[i]=c;

		i++;
	}
	command[i-1]='\0';
	char *t1=st1[++top].s;
	char *t2=command;
	char *t3;
	t3=strcpy(t1,t2);
	top++;
	//printf("pstring is %s\n",pstring);
	//exit(0);
	/*if(strcmp(command,"|")<0)
	  {
	  printf("jayesh\n");
	  piping(pstring);
	  }
	  wait(NULL);*/
	//	exit(0);

	/* 									MAIN CODE WHILE LOOP									*/
	while(strcmp(command,"quit")!=0)
	{

		mflag=0;
		//	int len=strlen(command);
		//	printf("%s %d\n",command,len);
		/*									CHECK FOR CD COMMAND										*/
		if(command[0]=='c' && command[1]=='d')
		{
			if(command[2]='\0')
			{
				/*char t[2];
				  t[0]='~';
				  t[1]='\0';
				  char *cptr=t;*/
				int x;
				x=chdir(buff2);
			}
			else if(command[2]=' ')
			{
				char *cptr=&command[3];
				int x=chdir(cptr);
			}
			st1[top-1].pid=-1;
			st1[top-1].flag=0;
			st1[top-1].pip=0;
			st1[top-1].red=0;
			mflag=1;

		}
		/*							CHECK FOR PID COMMAND AND DELIVER TO EXECPID FUNCTION 2 EXECUTE 						*/		
		else if(strcmp(command,"pid")==0)
		{
			execpid();
			/*int pid;
			  pid=getpid();
			  printf("command name: ./a.out process id:");
			  printf("%d\n",pid);
			  st1[top-1].pid=-1;
			  st1[top-1].flag=0;*/
			mflag=1;
			st1[top-1].pip=0;
			st1[top-1].red=0;
		}
		/*								CHECK FOR LS COMMAND AND EXECUTE IT HERE ONLY									*/		
		else if(strcmp(command,"ls")==0)
		{
			pid_t pid;
			pid=fork();
			if(pid==0)
			{
				int ret;
				ret=execlp("/bin/ls","ls",NULL);
				_exit(0);
			}
			if(pid>0)
			{
				wait(NULL);
			}
			st1[top-1].pid=-1;
			st1[top-1].flag=0;
			mflag=1;
			st1[top-1].pip=0;
			st1[top-1].red=0;

		}
		/*						CHECK FOR HIST COMMAND AND DELIVER TO EXECHIST FUNCTION  								*/		
		else if(strcmp(command,"hist")==0)
		{
			/*int j=0;
			//			j=top;
			while(j<=top-1)
			{
			printf("%s\n",st1[j].s);j++;
			}
			st1[top-1].pid=-1;
			st1[top-1].flag=0;
			mflag=1;
			st1[top-1].pip=0;
			st1[top-1].red=0;*/
			exechist();
		}
		/*						CHECK FOR HISTN COMMAND AND DIRECT TO EXECHISTN FUNCTION								*/		
		else if(strlen(command)==5 && command[0]=='h' && command[1]=='i' && command[2]=='s' && command[3]=='t')
		{
			/*int x=command[4]-48;
			  int i;
			  if(x>top)
			  {
			  for(i=0;i<=top-1;i++)
			  {
			  printf("%s\n",st1[i].s);
			  }
			  }
			  else
			  {
			  for(i=top-x;i<=top-1;i++)
			  {
			  printf("%s\n",st1[i].s);
			  }
			  }
			  st1[top-1].pid=-1;
			  st1[top-1].flag=0;
			  mflag=1;
			  st1[top-1].pip=0;
			  st1[top-1].red=0;*/
			exechistn(command);
		}
		/*				CHECK FOR !HISTN COMMAND AND DEAL IT HERE ONLY,CANT DEAL IF NTH COMMAND IS !HISTN AND CAN ALSO DEAL PID,HIST AND OTHER ASSGN COMMAND ALSO     */
		else if(command[0]=='!' && command[1]=='h' && command[2]=='i' && command[3]=='s' && command[4]=='t')
		{
			//printf("hello world\n");
			int x=command[5]-48;
			//printf("x is %d\n",x);
			//if(x>0 && x<=9)
			//{	

			char t1[500];
			char *t2=st1[x-1].s;
			char *t3;
			t3=strcpy(t1,t2);
			//	printf("t1 is %s\n",t1);
			if(strcmp(t1,"hist")==0)
			{
				exechist();
			}
			else if(strcmp(t1,"hist")<=0 && command[5]=='\0')
			{
				exechistn(command);
			}
			else if(strcmp(t1,"pid")==0)
			{
				execpid();
			}
			else if(strcmp(t1,"pidall")==0)
			{
				execpidall();
			}
			else if(strcmp(t1,"pidcurrent")==0)
			{
				execpidcurrent();
			}
			else
			{
				//printf("t3 is %s\n",t1);
				char *result=NULL;
				char *array[100];
				result=strtok(t1," ");
				int i=0;
				while(result!=NULL)
				{
					array[i]=result;
					//printf("%s is \n",array[i]);
					result=strtok(NULL," ");
					i++;
				}
				array[i]='\0';
				pid_t pid;
				pid=fork();
				if(pid==0)
				{
					int x=execvp(array[0],array);
					_exit(0);
				}
				else
				{
					//int status;
					wait(NULL);
				}
			}
			//}

			st1[top-1].pid=-1;
			st1[top-1].flag=0;
			mflag=1;
			st1[top-1].pip=0;
			st1[top-1].red=0;
			//printf("exited\n");
		}
		/* 							DEAL WITH PID ALL COMMANDS AND REDIRECT TO EXECPIDALL FUNCTION 							*/
		else if(strcmp(command,"pid all")==0)
		{
			/*int i;
			  printf("List of all processes spawned from this shell:\n");
			  for(i=0;i<top-1;i++)
			  {
			  if(st1[i].pid!=-1)
			  printf("command name: %s process id: %d\n",st1[i].s,st1[i].pid);
			  }
			  st1[top-1].pid=-1;
			  st1[top-1].flag=0;*/
			execpidall();
			mflag=1;
			st1[top-1].pip=0;
			st1[top-1].red=0;
		}
		/*						DEAL WITH PID CURRENT COMMANDS AND REDIRECT TO EXECPIDCURRENT FUNCTION							*/		
		else if(strcmp(command,"pid current")==0)
		{
			/*int x;
			  printf("List of currently executing processes spawned from this shell:\n");
			  for(x=0;x<top-1;x++)
			  {
			  if(st1[x].flag==1)
			  {
			  printf("command name: %s process id: %d\n",st1[x].s,st1[x].pid);
			  }
			  }
			  st1[top-1].pid=-1;*/
			execpidcurrent();
			mflag=1;
			st1[top-1].pip=0;
			st1[top-1].red=0;
		}
		int m=0;
		//int m1=0;
		int pflag=0;
		int rflag=0;
		/*						SCAN THE COMMAND FOR PIPE OR REDIRECTOR											*/		
		while(command[m]!='\0')
		{
			if(command[m]=='|')
			{
				pflag=1;
				//break;
			}
			if(command[m]=='<' || command[m]=='>')
			{
				rflag=1;
			}
			m++;

		}
		char pstring[500];
		t3=strcpy(pstring,command);
		/* 				CHECK IF COMMAND HAS PIPE OR REDIRECTION OR ANY OTHER NON USER DEFINED COMMANDS LIKE CAT GREP AND ALSO COMMANDS ENDING AT & 			*/	
		if(pflag==1 && mflag!=1)
		{
			//st1[top-1].pid=-1;
			//st1[top-1].flag=0;
			//printf("jayesh\n");
			piping(pstring);
			st1[top-1].pip=1;
		}
		else if(pflag==0 && mflag!=1 && rflag==1)
		{
			//st1[top-1].pid=-1;
			//st1[top-1].flag=0;
			//printf("ghusa\n");
			redirector(pstring);
			st1[top-1].pip=0;
			st1[top-1].red=1;
		}
		else if(pflag==0 && mflag!=1)
		{
			pid_t x=other_c(command);
			st1[top-1].pid=x;
			st1[top-1].pip=0;
			st1[top-1].red=0;
		}
		/*					PFLAG==FLAG FOR PIPE , RFLAG FOR REDIRECTION OPERATOR , MFLAG FOR ANY OTHER COMMAND							*/
		print();
		c='a';
		command[0]='\0';
		i=0;
		/* 										SCAN FOR NEW COMMAND								*/
		while(c!='\n')
		{
			scanf("%c",&c);

			if((c==' ' || c=='\t') && i==0)
				continue;
			if((c==' ' || c=='\t') && command[i-1]==' ')
				continue;
			else
				command[i]=c;
			i++;
		}
		/*						PUSHING THE COMMAND TO HISTORY STACK ALONG WITH FLAG FOR '&' , '|' ,'<' , '>' 					*/		
		command[i-1]='\0';
		char *t1=st1[top].s;
		char *t2=command;
		char *t3;
		t3=strcpy(t1,t2);
		top++;
		//		len=strlen(command);
		//		printf("%s %d\n",command,len);
		//	printf("%s %d",command,strlen(command));
	}
	return 0;
}
/*									HANDLER FUNCTION FOR CTRL+C								*/
void ctrlc_handler(int sig)
{
	signal(sig,SIG_IGN);
	printf("\n");
	print();
	signal(SIGINT,ctrlc_handler);
}
/*									FUNCTION TO PRINT PROMPT							*/
void print()
{
	int r,r1,r2;
	char s[100],s1[100],s2[100],s3[100];
	char *buff;
	buff=s2;
	r=gethostname(s,100);
	r1=getlogin_r(s1,100);
	buff=getcwd(buff,100);
	//	printf("s2 is %s\n",s2);
	if(strcmp("/home",s2)<0)
	{
		if(s2[5]=='/')
		{
			int i=6;
			while(s2[i]!='/' && i<strlen(s2))
			{
				i++;
			}
			//			printf("s2 ka last %c\n",s2[i+1]);
			if(s2[i]=='\0')
			{
				printf("<%s@%s:~>",s,s1);
				return;
			}
			i++; //i=8
			s3[0]='\0';
			int j=0;
			while(s2[i]!='\0')
			{
				s3[j]=s2[i];
				i++;
				j++;
			}
			s3[j]='\0';
			//			printf("s3 is %s\n",s3);
		}
		printf("<%s@%s:~/%s>",s,s1,s3);
		//		printf("hello\n");
	}
	else
	{
		//		printf("s2 is %s\n",s2);
		printf("<%s@%s:%s>",s,s1,s2);
	}
	fflush(stdout);
	return;
}
/*					FUNCTION TO EXECUTE ALL COMMAND WHICH ARE ALREADY SYSTEM PROGRAMS AND ALSO HANDLES BACKGROUND-FOREGRPUND CONCEPT			*/
pid_t other_c(char *s)
{
	//	printf("ghusaaa\n");

	char *result=NULL;
	char *array[100];
	char temp[100];
	char *y2;
	y2=strcpy(temp,s);
	result=strtok(temp," ");
	int i=0;
	//char temps[500];
	//temp=temps;
	//	printf("command is %s\n",temp);
	while(result!=NULL)
	{
		array[i]=result;
		//printf("%s is \n",array[i]);
		result=strtok(NULL," ");
		i++;
	}
	array[i]='\0';
	int j;
	/*for(j=0;j<i;j++)
	  {
	  printf("%s\n",array[j]);
	  }*/
	int flag=0;
	if(temp[strlen(s)-1]=='&')
	{
		flag=1;
		st1[top-1].flag=1;
	}
	//	return;
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		int x=execvp(array[0],array);
		_exit(0);
	}
	else if(pid>0 && flag==0)
	{
		int status;
		wait(&status);
		//_exit(0);
	}
	return pid;
}
/*						HANDLER FUNCTION TO CONTROL EXITING OR RETURNING OF BACKGROUND PROCESS							*/
void child_handler(int signum)
{
	int pid;
	pid = waitpid(WAIT_ANY, NULL, WNOHANG);
	int i;
	if(pid==-1 || pid==0)
	{
		return;
		//printf("child Dead\n");
	}
	for(i=0;i<top;i++)
	{
		if(st1[i].pid==pid)
		{
			//char t2[500];
			//char *tp;
			//tp=t2;
			//tp=strcpy(tp,st1[i].s);
			printf("\n%s %d exited normally\n",st1[i].s,st1[i].pid); 
			st1[i].flag=0;
			break;
		}
	}
	print();
	signal(SIGCHLD, child_handler);
	return;
}
/*										    FUNCTION TO CONTROL PIPE							*/	
/*									 HANDLES ONLY PIPE OR PIPE + REDIRECTION OPERATOR 					*/
/*								WILL ALSO HANDLE IF COMMAND BETWWEN PIPES IS PID ,PIDCURRENT OR LIKE COMMAND 			*/
void piping(char *s)
{
	char *result=NULL;
	char *array[100];
	char *t1;
	char temp[500];
	t1=strcpy(temp,s);
	result=strtok(temp,"|");
	int i=0;
	while(result!=NULL)
	{
		array[i]=result;
		result=strtok(NULL,"|");
		i++;
	}
	array[i]='\0';
	int j;
	int fd[100][2];
	char *array1[100];
	char dc[100];
	int k=0;
	pid_t pid;
	//1 write
	//0 read
	int redflag;
	for(k=0;k<i;k++)
	{
		int pidflag=0;
		int pidallflag=0;
		int pidcurrentflag=0;
		int histflag=0;
		int histnflag=0;
		t1=strcpy(dc,array[k]);
		//printf("dc is %s",dc);
		if(strcmp(dc,"pid ")==0)
		{
			pidflag=1;
			//printf("true\n");
		}
		else if(strcmp(dc,"pid all ")==0)
		{
			pidallflag=1;
		}
		else if(strcmp(dc,"pid current ")==0)
		{
			//printf("true\n");
			pidcurrentflag=1;
		}
		else if(strcmp(dc,"hist ")==0)
		{
			//printf("true\n");
			histflag=1;
		}
		else if(strcmp(dc,"histn ")<0 && dc[6]=='\0')
		{
			//printf("true\n");
			histnflag=1;
		}
		if(k!=0)
			close(fd[k-1][1]);
		pipe(fd[k]);
		pid=fork();
		int fx;
		if(pid==0)
		{
			redflag=0;
			char in[500];
			in[0]='\0';
			char ot[500];
			ot[0]='\0';
			char *ip=in;
			char *op=ot;
			getargs(array1,dc,ip,op);


			close(fd[k][0]);
			if(in[0]!='\0' && ot[0]=='\0')
			{
				//printf("aaya\n");
				int len=strlen(in);
				//printf("%s %d\n",in,len);
				in[len-1]='\0';
				fx=open(in, O_RDONLY);
				dup2(fx,STDIN_FILENO);
				close(fx);
				dup2(fd[k][1], STDOUT_FILENO);
				//if(fork()==0)
				//{
				execvp(array1[0],array1);
				//}
				close(fd[k][1]);
				//printf("waps\n");
				//else
				//{
				//wait(NULL);
				redflag=1;
				st1[top-1].red=1;
				//}
				//close(fx);
			}
			else if(in[0]=='\0' && ot[0]!='\0')
			{
				fx=open(ot, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
				dup2(fx,STDOUT_FILENO);
				redflag=2;
				st1[top-1].red=1;
			}
			/*if(redflag==1)
			  {
			//dup2(fx,STDIN_FILENO);
			dup2(fd[k][1], STDOUT_FILENO);
			//close(fd[k][0]);
			//close(STDIN_FILENO);
			execvp(array1[0],array1);
			//	wait(NULL);
			}*/
			if(redflag==2)
			{
				dup2(fd[k-1][0],STDIN_FILENO);
				dup2(fx,STDOUT_FILENO);
				execvp(array1[0],array1);
				close(fx);
			}
			else if(redflag==0)
			{
				st1[top-1].red=0;
				if(k!=0)
					dup2(fd[k-1][0], STDIN_FILENO);
				if(k!=i-1)
					dup2(fd[k][1], STDOUT_FILENO);
				if(pidflag==1)
				{
					execpid();
					_exit(0);
				}
				else if(pidallflag==1)
				{
					execpidall();
					_exit(0);
				}
				else if(pidcurrentflag==1)
				{
					execpidcurrent();
					_exit(0);
				}
				else if(histflag==1)
				{
					exechist();
					_exit(0);
				}
				else if(histnflag==1)
				{
					exechistn(dc);
					_exit(0);
				}
				else
					execvp(array1[0],array1);

			}
		}
		else if(pid>0)
		{

			wait(NULL);
		}
		/*if(k==0)
		  {
		  strcpy(st1[top-1].s,dc);
		  st1[top-1].pid=pid;
		  }
		  else
		  {
		  strcpy(st1[top].s,dc);
		  st1[top].pid=pid;
		  top++;
		  }*/
		//			printf("exited3\n");
	}

	//while(waitpid(-1, NULL, 0) != -1);
}

/*							A PARSING TO FN TO PARSE COMMANDS OF PIPE OR REDIRECTION FOR STRTOK WITH DELIME=" " 					*/
/*	              	EG:- IF COMMAND IS A | B | C , SO PIPING FN WILL SEND HIM A THEN B AND THEN C SO HE WILLPARSE A BY SPACAES EG, LS -AL TO LS AND -AL				*/
void getargs(char **array1,char *cmd,char *ip,char *op)
{
	char *result=NULL;
	char temp[100];
	strcpy(temp,cmd);
	int inflag=0;
	int outflag=0;
	int inindex=0;
	int outindex=0;
	int i=0;
	while(temp[i]!='\0')
	{
		if(temp[i]=='<')
		{	
			inflag=1;
			inindex=i;
		}
		if(temp[i]=='>')
		{	
			outflag=1;
			outindex=i;
		}
		i++;

	}
	//	printf("temp is %s\n",temp);
	//	printf("inflag is %d outflag is %d and inindex is %d and outindex is %d\n",inflag,outflag,inindex,outindex);
	if(inflag==1 && outflag!=1)
	{
		op[0]='\0';
		int j=inindex+2;
		int k=0;
		while(temp[j]!='\0')
		{
			ip[k]=temp[j];
			j++;
			k++;
		}
		ip[k]='\0';
		temp[inindex-1]='\0';

	}
	else if(inflag!=1 && outflag==1)
	{
		ip[0]='\0';
		int j=outindex+2;
		int k=0;
		while(temp[j]!='\0')
		{
			op[k]=temp[j];
			j++;
			k++;
		}
		op[k]='\0';
		temp[outindex-1]='\0';
	}
	//	printf("temp now is %s and in is %s and out is %s\n",temp,ip,op);
	result=strtok(temp," ");
	i=0;
	while(result!=NULL)
	{
		array1[i]=result;
		result=strtok(NULL," ");
		i++;
	}
	array1[i]='\0';
	int j;
	//	printf("fn\n");
	//	for(j=0;j<i;j++)
	//		printf("fn %s ",array1[j]);
}
/*							FUNCTION TO HANDLE ONLY REDIRECTORS WITHOUT PIPING,I.E A < B OR A > B OR A < B > C		*/
void redirector(char *t)
{
	char cmd[200];
	char *t2;
	t2=strcpy(cmd,t);
	//printf("cmd is %s\n",cmd);
	char command[100];
	char input[100];
	char output[100];
	int i=0;
	int j=0;
	int flag=0;
	int k=strlen(t2);
	command[0]='\0';
	input[0]='\0';
	output[0]='\0';
	while(i!=k)
	{
		if(cmd[i]=='<')
		{
			flag=1;
			command[j-1]='\0';
			j=0;
			i+=2;
			continue;
		}
		else if(cmd[i]=='>')
		{
			if(flag==0)
			{
				command[j-1]='\0';
				j=0;
			}
			if(flag==1)
			{
				input[j-1]='\0';
				j=0;
			}
			flag=2;
			i+=2;
			continue;
		}
		if(flag==0)
		{
			command[j]=cmd[i];
			j++;
			i++;
		}
		else if(flag==1)
		{
			input[j]=cmd[i];
			i++;
			j++;
		}
		else if(flag==2)
		{
			output[j]=cmd[i];
			i++;
			j++;
		}
		//i++;
	}
	if(i==k)
		input[j]='\0';
	output[j]='\0';
	int cl=strlen(command);
	int il=strlen(input);
	int ol=strlen(output);
	int pidflag=0;
	int pidallflag=0;
	int pidcurrentflag=0;
	int histflag=0;
	int histnflag=0;
	if(strcmp(command,"pid")==0)
	{
		pidflag=1;
	}
	else if(strcmp(command,"pid all")==0)
	{
		pidallflag=1;
	}
	else if(strcmp(command,"pid current")==0)
	{
		//printf("true\n");
		pidcurrentflag=1;
	}
	else if(strcmp(command,"hist")==0)
	{
		//printf("true\n");
		histflag=1;
	}
	else if(strcmp(command,"hist")<=0 && command[5]=='\0')
	{
		//printf("true\n");
		histnflag=1;
	}
	//printf("%s %d\n%s %d\n%s %d\n",command,cl,input,il,output,ol);
	char *array1[100];
	char *t1;
	char *t3;
	getargs(array1,command,t1,t2);
	char *result;
	result=strtok(command," ");
	i=0;
	while(result!=NULL)
	{
		array1[i]=result;
		result=strtok(NULL," ");
		i++;
	}
	array1[i]='\0';
	int fx;
	int fx1;
	if(fork()==0)
	{
		if(input[0]!='\0' && output[0]!='\0')
		{
			fx=open(input, O_RDONLY);
			dup2(fx,STDIN_FILENO);
			close(fx);
			fx1=open(output, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			dup2(fx1,STDOUT_FILENO);
			execvp(array1[0],array1);
			close(fx1);
		}
		else if(input[0]=='\0' && output[0]!='\0')
		{
			//printf("aaya\n");
			fx=open(output, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			dup2(fx,STDOUT_FILENO);
			if(pidflag==1)
			{
				execpid();
				close(fx);
				_exit(0);
			}
			else if(pidallflag==1)
			{
				execpidall();
				close(fx);
				_exit(0);
			}
			else if(pidcurrentflag==1)
			{
				execpidcurrent();
				close(fx);
				_exit(0);
			}
			else if(histflag==1)
			{
				exechist();
				close(fx);
				_exit(0);
			}
			else if(histnflag==1)
			{
				exechistn(command);
				close(fx);
				_exit(0);
			}
			else
			{
				execvp(array1[0],array1);
				close(fx);
			}

		}
		else if(input[0]!='\0' && output[0]=='\0')
		{
			fx=open(input, O_RDONLY);
			dup2(fx,STDIN_FILENO);
			close(fx);
			execvp(array1[0],array1);
		}
	}
	else
	{
		wait(NULL);
	}
}
/*											FN TO EXECUTE PID						*/
void execpid()	
{
	int pid;
	pid=getpid();
	printf("command name: ./a.out process id:");
	printf("%d\n",pid);
	st1[top-1].pid=-1;
	st1[top-1].flag=0;
	//int mflag=1;
}
/*											FN TO EXECUTE PID ALL						*/
void execpidall()
{
	int i;
	printf("List of all processes spawned from this shell:\n");
	for(i=0;i<top-1;i++)
	{
		if(st1[i].pid!=-1)
			printf("command name: %s process id: %d\n",st1[i].s,st1[i].pid);
	}
	st1[top-1].pid=-1;
	st1[top-1].flag=0;
}
/*											FN TO EXECUTE PID CURRENT					*/
void execpidcurrent()
{
	int x;
	printf("List of currently executing processes spawned from this shell:\n");
	for(x=0;x<top-1;x++)
	{
		if(st1[x].flag==1)
		{
			printf("command name: %s process id: %d\n",st1[x].s,st1[x].pid);
		}
	}
	st1[top-1].pid=-1;
	st1[top-1].flag=0;

}
/*										FN TO EXECUTE HISTORY COMMANS						*/
void exechist()
{
	int j=0;
	//			j=top;
	while(j<=top-1)
	{
		printf("%s\n",st1[j].s);j++;
	}
	st1[top-1].pid=-1;
	st1[top-1].flag=0;
	mflag=1;
	st1[top-1].pip=0;
	st1[top-1].red=0;

}
/*										FN TO EXECUTE HISTN COMMAND							*/
void exechistn(char command[])
{
	int x=command[4]-48;
	int i;
	if(x>top)
	{
		for(i=0;i<=top-1;i++)
		{
			printf("%s\n",st1[i].s);
		}
	}
	else
	{
		for(i=top-x;i<=top-1;i++)
		{
			printf("%s\n",st1[i].s);
		}
	}
	st1[top-1].pid=-1;
	st1[top-1].flag=0;
	mflag=1;
	st1[top-1].pip=0;
	st1[top-1].red=0;
}
