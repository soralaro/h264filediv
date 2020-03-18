#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	printf("start!\n");

	//fstream file("nums.dat", ios::out | ios::binary);
	//file.open("nums.dat", ios::in);
	//file.read(reinterpret_cast<char *>(buffer), sizeof (buffer));
	//file.close ();
	std::fstream file_in("tt_2.h264", std::ios::in);
	file_in.seekg(0, std::ios::end);
        long file_in_size = file_in.tellg();
        file_in.seekg(0, std::ios::beg);
	unsigned char *buffer_in= new unsigned char[file_in_size];
	memset(buffer_in,0,file_in_size);
 	//long read_len=
 	file_in.read(reinterpret_cast<char *>(buffer_in), file_in_size);
 	//printf("file_in_size=%ld, read_len=%ld\n",file_in_size, read_len);
 	unsigned char state=0;
 	long start=-1;
 	long end=0;
 	long sn=0;
        FILE *out_list=fopen("out.list","w");
 	for(long i=0;i<file_in_size;i++)
 	{
 		//printf(" %02x",buffer_in[i]);
 		if(buffer_in[i]==0x00)
 		{
 			if(state==0)
 			{
 				state=1;
 				printf("%d ",state);
 			}
 			else if(state==1)
 			{
 				state=2;
 				printf("%d ",state);
 			}
 			else if(state==2)
 			{
 				state=3;
 				printf("%d ",state);
 			}
 			else
 			{
 				state=0;
 				printf("%d ",state);
 			}
 		}
 		else if(buffer_in[i]==0x01)
 		{
 			if(state==3)
 			{
 				state=4;
 				printf("%d \n",state);
 				if(start!=-1)
 				{
 					end=i-4;

 					std::string out_file_name="./out_H264/"+std::to_string(sn)+".h264";
 					printf("%s\n",out_file_name.c_str());
 					std::fstream file_out(out_file_name, std::ios::out | std::ios::binary);
 					file_out.write(reinterpret_cast<char *>(buffer_in+start),end-start+1);
 					file_out.close();
                                        fprintf(out_list,out_file_name.c_str());
                                        fprintf(out_list,"\n");
 					sn++;
 				}
 				start=i-3;
 			}
 			else
 			{
 				state=0;
 			}
 		}
 		else
 		{
 			state=0;
 		}
 	}
 	printf("\n");
	file_in.close ();
        fclose(out_list);
    delete [] buffer_in;

}
