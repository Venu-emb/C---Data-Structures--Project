#include"header.h"

void main() 
{
	SLL *headptr=0;
	char op;
	while(1) 
        {
		printf("\033[0;36;1;4m****STUDENT RECORDS MENU****\033[0m\n");
		printf("\033[0;36;1ma/A : add_new_record\nd/D : delete_a_record\ns/S : show_the_list\nm/M : modify_the_records\nv/V : save_data_into_file\nt/T : sort_the_list\nl/L : delete_all_records\nr/R : reverse_the_records\ne/E : exit\nK/k : read_file\nEnter your choice :\033[0m\n");
		scanf("%c",&op);

		if(op>='A' && op<='Z')
			op=op+32;

		switch(op) 
                {

			case 'a':add_new_record(&headptr);
				 break;
			case 's':show_the_list(headptr);
				 break;
			case 'd':delete_a_record(&headptr);
				 break;
			case 'm':modify_the_records(&headptr);
				 break;
			case 'v':save_data_into_file(headptr);
				 break;
			case 'e':exit_pgm(&headptr);
				 break;
			case 't':sort_the_list(headptr);
				 break;
			case 'l':delete_all_records(&headptr);
				 break;
			case 'r':reverse_the_records(headptr);
				 break;
			case 'k':read_file(&headptr);
				 break;
                        default :printf("\033[0;31;1mYou Have Entered Wrong Option,Please Choose Correct Option\033[0m\n");
		}   
	}
}


void add_new_record(SLL **ptr) 
{
	SLL *new;

	static int rollno=1;

	new=malloc(sizeof(SLL));

	new->next=0;

	printf("\033[0;35;1mEnter Student Name and Percentage :\033[0m\n");
	scanf("%s%f",new->name,&new->percentage);

	SLL *r1,*r2;
	r1=*ptr;

	if(*ptr) 
        {

		r2=r1->next;
		if(r1->rollno != 1)
			new->rollno=1;

		else 
                {
			while(r2) 
                         {
				if((r1->rollno) != (r2->rollno)-1) 
                                {
					new->rollno=r1->rollno + 1;
					break;
				}
				r1=r1->next;
				r2=r2->next;
			}
			if(r2==0)
				new->rollno=r1->rollno + 1;
		}
	}


	if(*ptr==0) 
        {
		new->rollno=rollno;
		rollno++;
		*ptr=new;
	}


	else  
         {
		SLL *p1,*p2;

		int i,j;

		int c=count_node(*ptr);
		p1=*ptr,p2;
		p2=p1;
		for(i=0;i<c;i++) 
                { 
			if((p1->rollno) > (new->rollno) )  
                        {
				new->next=p1;
				if(*ptr==p1)
					*ptr=new;
				else
					p2->next=new;
				return;
			}
			p2=p1;
			p1=p1->next;
		}
		p2->next=new;
	}
        printf("\033[0;32;1mStudent Record Successfully Added\033[0m\n");
}

void delete_a_record(SLL **ptr) 
{
	if(*ptr==0)  
        {
		printf("\033[0;31;1mNo Records found\033[0m\n");
		return;
	}
	char op;
	printf("\033[0;35;1mR/r : enter roll to delete\nN/n : enter name to delete\033[0m\n");
	scanf(" %c",&op);

	if(op=='R' || op=='N' )
		op=op+32;
        if(op!='r'&&op!='n')
        printf("\033[0;31;1mYou Have Entered Wrong Option\033[0m\n");

	if(op=='r') 
        {
		int num;
		printf("\033[0;35;1mPlease Enter Rollno\033[0m\n");
		scanf("%d",&num);
		SLL *del=*ptr,*prev;
		prev=0;
		while(del) 
                {
			if(del->rollno==num) 
                        {
				if(prev==0)
					*ptr=del->next;
				else
					prev->next=del->next;
				free(del);
                                printf("\033[0;32;1mStudent Record Deleted Successfully\033[0m\n");
				return;
			}
			prev=del;
			del=del->next;
		}
		printf("\033[0;31;1mRoll Number Not Found\033[0m\n");
	}

	if(op=='n')
        {
		char name[20];
		printf("\033[0;35;1mPlease Enter Name\033[0m\n");
		scanf("%s",name);
		SLL *del1,*del2,*prev1,*p4;
		del1=*ptr;
		while(del1) 
                {
			if(strcmp(name,del1->name)==0)
                        {
		        del2 = del1->next;
                        p4=del1->next;
                        break;
			}
                        prev1=del1;
		        del1=del1->next;
		}
                if(del1==0)
                {
			printf("\033[0;31;1mName not found\033[0m\n");
                        return;
                }

		while(del2)
                {
			if(strcmp(name,del2->name)==0) 
                        {
				int r1;
				printf("\033[0;35;1msome students having same name please enter rollno to delete\033[0m\n");
				scanf("%d",&r1);
				SLL *del,*prev;
				del=*ptr;
				while(del)
                                {
					if(r1==del->rollno)
                                        {
			                        if(del==*ptr)
                                                *ptr=del->next;
                                                else
                                                prev->next=del->next;
                                                free(del);
                                                printf("\033[0;32;1mStudent Record Deleted Successfully\033[0m\n");
						return;
					}
                                        prev=del;
					del=del->next;
				}
					printf("\033[0;31;1mRollno not found\033[0m\n");
			}
			del2=del2->next;
		}
		if(del2==0)
		{
			if(p4==0)
				*ptr=del1->next;
			else
				prev1->next=del1->next; 
			free(del1);
                        printf("\033[0;32;1mStudent Record Deleted Successfully\033[0m\n");
		}

	}
}

void modify_the_records(SLL **ptr) 
{
	char op;
	int r;
	SLL *p1;
	p1=*ptr;
	printf("\033[0;35;1mEnter which record to search for modification\nR/r : to search a rollno\nN/n : to search a name\nP/p : percentage based\033[0m\n");
	scanf(" %c",&op);

	if(op>='A'&&op<='Z')
		op=op+32;
        
        if(op!='r'&&op!='n'&&op!='p')
        printf("\033[0;31;1mYou Have Entered Wrong Option\033[0m\n");

	if(op=='r') 
        {
		printf("\033[0;35;1menter roll number\033[0m\n");
		scanf("%d",&r);
		while(p1) 
                {
			if(r==p1->rollno)
                        {
				printf("\033[0;35;1mplease enter name and percentage\033[0m\n");
				scanf("%s%f",p1->name,&p1->percentage);
                                printf("\033[0;32;1mStudent Data Modified Successfully\033[0m\n");
				return;
			}
			p1=p1->next;
		}
			printf("\033[0;31;1mRoll Number Not Found\033[0m\n");
	}

	if(op=='n')
        {
		char name[20];
		SLL *p2;
		int f=0;
		printf("\033[0;35;1menter name\033[0m\n");
		scanf("%s",name);
		while(p1) 
                {
			if(strcmp(name,p1->name)==0)
                        {
				p2=p1->next;
				break;
			}
			p1=p1->next;
		}
		if(p1==0)
                {
			printf("\033[0;31;1mName not found\033[0m\n");
			return;
		}
		while(p2)
                {
			if(strcmp(name,p2->name)==0) 
                        {
				int r1;
				printf("\033[0;35;1msome students having same name please enter rollno to modify\033[0m\n");
				scanf("%d",&r1);
				SLL *p3;
				p3=*ptr;
				while(p3)
                                {
					if(r1==p3->rollno)
                                        {
						f=1;
						printf("\033[0;35;1mplease enter name and percentage\033[0m\n");
						scanf("%s%f",p3->name,&p3->percentage);
                                                printf("\033[0;32;1mStudent Data Modified Successfully\033[0m\n");
						break;
					}
					p3=p3->next;
				}
				if(p3==0)
					printf("\033[0;31;1mRollno not found\033[0m\n");
			}
			if(f==1)
				break;
			p2=p2->next;
		}
		if(p2==0)
                {
			printf("\033[0;35;1mplease enter name and percentage\033[0m\n");
			scanf("%s%f",p1->name,&p1->percentage);
                        printf("\033[0;32;1mStudent Data Modified Successfully\033[0m\n");
		}
	}

	if(op=='p') 
        {
		float f1;
		int f2;
		SLL *p1,*p2;
		p1=*ptr;
		printf("\033[0;35;1mEnter Percentage\033[0m\n");
		scanf("%f",&f1);
		while(p1) 
                {
			if(p1->percentage==f1)
                        {
				p2=p1->next;
				break;
			}
			p1=p1->next;
		}
		if(p1==0)
                {
			printf("\033[0;31;1mNo students having %f percentage\033[0m\n",f1);
			return;
		}

		while(p2)
                {
			if(p2->percentage==f1) 
                        {
				int r1;
				printf("\033[0;35;1msome students having same percentage please enter rollno to modify\033[0m\n");
				scanf("%d",&r1);
				SLL *p3;
				p3=*ptr;
				while(p3)
                                {
					if(r1==p3->rollno)
                                        {
						f2=1;
						printf("\033[0;35;1mplease enter name and percentage\033[0m\n");
						scanf("%s%f",p3->name,&p3->percentage);
                                                printf("\033[0;32;1mStudent Data Modified Successfully\033[0m\n");
						break;
					}
					p3=p3->next;
				}
				if(p3==0)
					printf("\033[0;31;1mRollno not found\033[0m\n");
			}
			if(f2==1)
				break;
			p2=p2->next;
		}
		if(p2==0)
                {
			printf("\033[0;35;1mplease enter name and percentage\033[0m\n");
			scanf("%s%f",p1->name,&p1->percentage);
                        printf("\033[0;32;1mStudent Data Modified Successfully\033[0m\n");
		}
	}
}

void save_data_into_file(SLL *ptr) 
{
	if(ptr==0) 
        {
		printf("\033[0;31;1mRecords Not Found\033[0m\n");
		return;
	}
	FILE *fp;
	fp=fopen("stud.data","w");
	while(ptr) 
        {
		fprintf(fp,"%d %s %f\n",ptr->rollno,ptr->name,ptr->percentage);
		ptr=ptr->next;
	}
	printf("\033[0;32;1mData Saved in File\033[0m\n");
	fclose(fp);
}

void read_file(SLL **ptr) 
{
	SLL *new,*last;
	FILE *fp=fopen("stud.data","r");
	if(fp==0)
        {
		printf("\033[0;31;1mStudent Database Notfound\033[0m\n");
		return;
	}
	while(1) 
        {
		new=malloc(sizeof(SLL));
		if(fscanf(fp,"%d %s %f",&new->rollno,new->name,&new->percentage)==-1) 
                {
			free(new);
			break;
		}
		new->next=0;
		if(*ptr==0)
			*ptr=new;
		else
                {
			last=*ptr;
			while(last->next)
				last=last->next;
			last->next=new;
		}

	}
        printf("\033[0;32;1mData Successfully Fetched\033[0m\n");
}

void exit_pgm(SLL **p) 
{
	char op;

	printf("\033[0;35;1mS/s : save and exit\nE/e : exit without saving\033[0m\n");
	scanf(" %c",&op);

	if(op>='A'&&op<='Z')
		op=op+32;

        if(op!='s'&&op!='e')
        printf("\033[0;31;1mYou Have Entered wrong Option\033[0m\n");

	if(op=='s')
        {
		save_data_into_file(*p);
		printf("\033[0;32;1mexited\033[0m\n");
	}
	if(op=='e')
		printf("\033[0;32;1mexited without saving\033[0m\n");
}

void sort_the_list(SLL *ptr) 
{
	if(ptr==0) 
        {
		printf("\033[0;31;1mNo records found\033[0m\n");
		return;
	}
	char op;
	printf("\033[0;35;1mChoose the Sorting Option\nN/n : sort with name\nP/p : sort wit percentage\033[0m\n");
	scanf(" %c",&op);
	if(op>='A'&&op<='Z')
		op=op+32;
        if(op!='n'&&op!='p')
        printf("\033[0;31;1mYou have entered wrong option\033[0m\n");

	if(op=='n') 
        {
		SLL *p1=ptr,*p2,temp;
		int i,j,c=count_node(ptr);
		for(i=0;i<c-1;i++)
                {
			p2=p1->next;
			for(j=0;j<c-1-i;j++) 
                        {
				if(strcmp(p1->name,p2->name)>0) 
                                {
					temp.rollno=p1->rollno;
					strcpy(temp.name,p1->name);
					temp.percentage=p1->percentage;
					p1->rollno=p2->rollno;
					strcpy(p1->name,p2->name);
					p1->percentage=p2->percentage;
					p2->rollno=temp.rollno;
					strcpy(p2->name,temp.name);
					p2->percentage=temp.percentage;
				}
				p2=p2->next;
			}
			p1=p1->next;
		}
                printf("\033[0;32;1mList Sorted Successfully\033[0m\n");
	}

	if(op=='p') 
        {
		SLL *p1=ptr,*p2,temp;
		int i,j,c=count_node(ptr);
		for(i=0;i<c-1;i++)
                {
			p2=p1->next;
			for(j=0;j<c-1-i;j++) 
                        {
				if(p1->percentage>p2->percentage) 
                                {
					temp.rollno=p1->rollno;
					strcpy(temp.name,p1->name);
					temp.percentage=p1->percentage;
					p1->rollno=p2->rollno;
					strcpy(p1->name,p2->name);
					p1->percentage=p2->percentage;
					p2->rollno=temp.rollno;
					strcpy(p2->name,temp.name);
					p2->percentage=temp.percentage;
				}
				p2=p2->next;
			}
			p1=p1->next;
	        }
                printf("\033[0;32;1mList Sorted Successfully\033[0m\n");
	}
}

void delete_all_records(SLL **ptr) 
{
	if(*ptr==0) 
        {
		printf("\033[0;31;1mNo Records found\033[0m\n");
		return;
	}
	int c=1;
	SLL *del=*ptr;
	while(del)
        {
		*ptr=del->next;
		free(del);
		del=*ptr;
	}
	printf("\033[0;32;1mAll records are successfully deleted\033[0m\n");
}

void reverse_the_records(SLL *ptr) 
{
	if(ptr==0) 
        {
		printf("\033[0;31;1mNo Records found\033[0m\n");
		return;
	}
	SLL *temp;
	int i,j,c=count_node(ptr);
	for(i=0;i<c;i++) 
        {
		temp=ptr;
		for(j=1;j<c-i;j++)
			temp=temp->next;
		printf("\033[0;34;1m%d %s %f\033[0m\n",temp->rollno,temp->name,temp->percentage);
	}
}

int count_node(SLL *ptr) 
{
	int c=0;
	while(ptr) 
        {
		c++;
		ptr=ptr->next;
	}
	return c;
}

void show_the_list(SLL *ptr) 
{

	if(ptr==0) 
        {
		printf("\033[0;31;1mNo Records Found...\033[0m\n");
		return;
	}
        printf("\033[0;37;1mThis is the List : \033[0m\n");
	while(ptr) 
        {
		printf("\033[0;34;1m%d %s %f\033[0m\n",ptr->rollno,ptr->name,ptr->percentage);
		ptr=ptr->next;
	}
}
