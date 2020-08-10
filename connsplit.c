#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>



int main(int argc,char **argv)
{
	char command[100],buf[100];
	char ch[100],*val1=NULL,*val2=NULL,*val3=NULL,*val4=NULL;
	int n,c;
	
	while ((c = getopt (argc, argv, "i:o:j:f:")) != -1)
    		switch (c)
      		{
      		case 'i':
        		//printf("\n\nInside -i\n\n");
				val1=optarg;	
        		break;

      		case 'o':
        		//printf("\n\nInside -o\n\n");
				val2=optarg;
				snprintf(buf,sizeof(buf),"mkdir -p %s",val2);
				system(buf);
       			break;
       		case 'j':
        		//printf("\n\nInside -o\n\n");
				val3=optarg;
				snprintf(buf,sizeof(buf),"mkdir -p %s",val3);
				system(buf);
       			break;
       		case 'f':
        		//printf("\n\nInside -o\n\n");
				val4=optarg;
       			break;
      		case '?':
        		if (optopt == 'i' || optopt == 'o'||optopt == 'j' || optopt == 'f')
          			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        		else if (isprint (optopt))
          			fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        		else
          			fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
        			return 1;
      		default:
        		abort ();
      }

      if(val1==NULL || val2== NULL)
      {
      	printf("\nThe pcap file name and the output directory is necessary.\n");
      	exit(0);
      }


      else
      {
      	snprintf(buf,sizeof(buf),"echo $(expr `tshark -r %s.pcap -T fields -e tcp.stream | sort -n | uniq | wc -l` - 2 >temp.txt)",val1);
		FILE *fp;
		fp = fopen("temp.txt", "r");
		fscanf (fp, "%d", &n); 
		fclose(fp);

		if(val4!=NULL)
      	{
      		for(int i = 0; i <=n; i++)
       		{
      			snprintf(buf,sizeof(buf),"tshark -r %s.pcap -Y \"ip.src==%s and ip.dst==%s\" -w %s/%d.pcap -2 -R \"tcp.stream==%d\"",val1,val4,val4,val2,i,i);
				system(buf);
        	}

      	}
      	else
      	{

      	
			for(int i = 0; i <=n; i++)
       		{
           	 	snprintf(buf,sizeof(buf),"tshark -r %s.pcap -w %s/%d.pcap -2 -R \"tcp.stream==%d\"",val1,val2,i,i);
           	 	system(buf);
        	}

        }
      }

      if(val3!=NULL)
      {		

      		snprintf(buf,sizeof(buf),"tshark -r %s.pcap -w %s/%s.pcap -Y \"not tcp\"",val1,val3,"nontcp");
           	system(buf);

      }


	
	return(0);
}