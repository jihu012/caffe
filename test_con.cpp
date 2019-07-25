#include<opencv2/opencv.hpp> 
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


using namespace cv;
using namespace std;

void max_pooling(double ***a,int m_rsize,int m_csize,int channel,unsigned char type);
void convolution(double ***a,int m_rsize,int m_csize,int channel,unsigned char type);





int main()
{
	Mat image;
	int x,y;
	int i,j,k;
	

	int channel;
	int padding;
	int stride;
	int selection;
	unsigned char type;
	double result;

	double ***p;

	clock_t start,end;
	start=clock();
	image=imread("test.jpg",IMREAD_COLOR); //이미지 파일 불러오
	if(image.empty())
	{
		cout<<"could not open or find the image"<<endl;
		return -1;
	}
	
	printf("체널의 수를 입력해 주세요:");
	scanf("%d",&channel);


	p=(double ***)malloc(channel*sizeof(double**));//3차원 배열 동적할당

	for(i=0;i<channel;i++)	
	{
		*(p+i)=(double**)malloc(image.rows*sizeof(double*));
			for(j=0;j<image.rows;j++)
			{
				*(*(p+i)+j)=(double*)malloc(image.cols*sizeof(double));
			}
	}


	for(i=0;i<channel;i++)
	{
		for(j=0;j<image.rows;j++)
		{
			for(k=0;k<image.cols;k++)
			{
				cv::Vec3b pixel=image.at<cv::Vec3b>(j,k);
				p[i][j][k]=image.at<cv::Vec3b>(j,k)[i];
			}
		}
	}
	
	
	type=image.type();

	printf("원하시는 방법을 선택해 주세요:\n1.Max pooling\n2.convolution 계산\n");
	scanf("%d",&selection);

	
	if(selection==1)
	{
		max_pooling(p,image.rows,image.cols,channel,type);
	}
	else if(selection==2)
	{
		convolution(p,image.rows,image.cols,channel,type);
	}
	else 
	{
		printf("wrong number");
	}

	

	for(i=0;i<channel;i++)//할당해제
	{
		for(j=0;j<image.rows;j++)
		{
			
			free(*(*(p+i)+j));
		}
		free(*(p+i));
	}
	free(p);
	end=clock();
	result=(double)(end-start);
	printf("\n%f\n",result);

return 0;


}

void max_pooling(double ***p,int m_rsize,int m_csize,int channel,unsigned char type)
{
		
	
	int i,j,k,l,m;
	

	double ***p1;

	
	double ***p2;
	int f_size;

	double ***p3;
	int p_rsize;
	int p_csize;
	int stride;

	double max=0;

	

	p1=(double***)malloc(channel*sizeof(double**));//3차원 배열 동적할당

	for(i=0;i<channel;i++)	
	{
		*(p1+i)=(double**)malloc(m_rsize*sizeof(double*));
			for(j=0;j<m_rsize;j++)
			{
				*(*(p1+i)+j)=(double*)malloc(m_csize*sizeof(double));
			}
	}


	for(i=0;i<channel;i++)
	{
		for(j=0;j<m_rsize;j++)
		{
			for(k=0;k<m_csize;k++)
			{
			p1[i][j][k]=p[i][j][k];
			}
		}
	}



	printf("필터 행렬의 크기를 입력하세요:");
	scanf("%d",&f_size);
	
	p2=(double***)malloc(channel*sizeof(double**));//3차원 배열 동적할당

	for(i=0;i<channel;i++)	
	{
		*(p2+i)=(double**)malloc(f_size*sizeof(double*));
			for(j=0;j<f_size;j++)
			{
				*(*(p2+i)+j)=(double*)malloc(f_size*sizeof(double));
			}
	}


	printf("stride의 크기를 입력하세요:");
	scanf("%d",&stride);
	
	
		
	p_rsize=(m_rsize-f_size)/stride+1;
	p_csize=(m_csize-f_size)/stride+1;




	

	p3=(double***)malloc(channel*sizeof(double**));

	for(i=0;i<channel;i++)
	{
		*(p3+i)=(double**)malloc(p_rsize*sizeof(double*));
		for(j=0;j<p_rsize;j++)
		{
			*(*(p3+i)+j)=(double*)malloc(p_csize*sizeof(double));
		}	
	}






       for(m=0;m<channel;m++)
	{	
	
			for(i=0;i<p_rsize;i++)
			{
				for(j=0;j<p_csize;j++)
				{
					for(k=0;k<f_size;k++)
					{
						for(l=0;l<f_size;l++)
						{
							if(max<p1[m][(i*stride)+k][(j*stride)+l])
							{
							max=(p1[m][(i*stride)+k][(j*stride)+l]);
							p3[m][i][j]=max;
							
							}
						}
							
					}			
                                        max=0; 
				}
					
				 
			}
		
	}
	

	cv::Mat max_pooling(p_rsize,p_csize,type);

	cv::Vec3b pixel=max_pooling.at<cv::Vec3b>(j,k);
	for(i=0;i<channel;i++)
	{
		for(j=0;j<p_rsize;j++)
		{
			for(k=0;k<p_csize;k++)
			{
				max_pooling.at<cv::Vec3b>(j,k)[i]=p3[i][j][k];
			}
		}
	}
	imshow("max_pooling",max_pooling);
	imwrite("max_pooling.jpg",max_pooling);
	

		for(i=0;i<channel;i++)//할당해제
	{
		for(j=0;j<p_rsize;j++)
		{
			
			free(*(*(p3+i)+j));
		}
		free(*(p3+i));
	}
	free(p3);
	
	
	
	for(i=0;i<channel;i++)//할당해제
	{
		for(j=0;j<f_size;j++)
		{
			
			free(*(*(p2+i)+j));
		}
		free(*(p2+i));
	}
	free(p2);


	for(i=0;i<channel;i++)//할당해제
	{
		for(j=0;j<m_rsize;j++)
		{
			
			free(*(*(p1+i)+j));
		}
		free(*(p1+i));
	}
	free(p1);

	




}
void convolution(double ***p,int m_rsize,int m_csize,int channel,unsigned char type)
{
	
	int i,j,k,l,m;
	

	double ***p1;
	
	int padding;
	int f_size;
	double ***p2;
	double ***p3;
	int ocsize;
	int orsize;
	int stride;
	int bigr;
	int bigc;
	double check_over=0;
	double sum=0;

	

	
	printf("패딩의 크기를 입력하세요:");				
	scanf("%d", &padding);

	printf("%d",padding);

	bigr=m_rsize+(padding*2);
	bigc=m_csize+(padding*2);
	
	p1=(double***)malloc(channel*sizeof(double**));//3차원 배열 동적할당
	
	for(i=0;i<channel;i++)	
	{
		*(p1+i)=(double**)malloc(bigr*sizeof(double*));
			for(j=0;j<bigr;j++)
			{
				*(*(p1+i)+j)=(double*)malloc(bigc*sizeof(double));
			}
	}

	
	for(i=0;i<channel;i++)
	{
		for(j=0;j<(bigr);j++)
		{
			for(k=0; k<(bigc); k++) 
				p1[i][j][k]=0;
		}
		
	}
	
	
	for(i=0;i<channel;i++)
	{
		for(j=0;j<m_rsize;j++)
		{
			for(k=0;k<m_csize;k++)
			{
				p1[i][j+padding][k+padding]=p[i][j][k];
			}
		}
	}
	
	printf("필터 행렬의 크기를 입력하세요:");
	scanf("%d",&f_size);

	
	p2=(double***)malloc(channel*sizeof(double**));//3차원 배열 동적할당

	for(i=0;i<channel;i++)	
	{
		*(p2+i)=(double**)malloc(f_size*sizeof(double*));
			for(j=0;j<f_size;j++)
			{
				*(*(p2+i)+j)=(double*)malloc(f_size*sizeof(double));
			}
	}
	
	printf("필터 행렬의 값을 입력하세요:");
	
	for(i=0;i<f_size;i++)
	{
			for(j=0;j<f_size;j++)
			{
			scanf("%lf",&p2[0][i][j]);
			}
	}

	for(i=0;i<f_size;i++)
	{
		for(j=0;j<f_size;j++)
		{
			check_over=check_over+p2[0][i][j];
		}		
	}
	
	for(i=1;i<channel;i++)
	{
		for(j=0;j<f_size;j++)
		{
			for(k=0;k<f_size;k++)
			{
			p2[i][j][k]=p2[0][j][k];
			}
		}
	}

	
	
	/*
        if(check_over>1)
	{	
		for(i=0;i<channel;i++)
			{
				for(j=0;j<f_size;j++)
					{
						for(k=0;k<f_size;k++)
						{
						p2[i][j][k]=(1/check_over)*p2[i][j][k];
						}
					}
	
                         }
	}
	*/ 

	printf("stride를 입력하세요:");
	scanf("%d",&stride);
	
	

	
	orsize=((m_rsize-f_size+(2*padding))/stride)+1;
	ocsize=((m_csize-f_size+(2*padding))/stride)+1;
	
	

	
	
	
	
	p3=(double***)malloc(channel*sizeof(double**));//3차원 배열 동적할당
	for(i=0;i<channel;i++)	
	{
		*(p3+i)=(double**)malloc(orsize*sizeof(double*));
			for(j=0;j<orsize;j++)
			{
				*(*(p3+i)+j)=(double*)malloc(ocsize*sizeof(double));
			}
	}
	
	
	

	 for(m=0;m<channel;m++)
	{	
	
			for(i=0;i<orsize;i++)
			{
				for(j=0;j<ocsize;j++)
				{
					for(k=0;k<f_size;k++)
					{
						for(l=0;l<f_size;l++)
						{
							p3[m][i][j]+=(p1[m][(i*stride)+k][(j*stride)+l])*p2[m][k][l];
				
						}
							
					}			
                                        if(p3[m][i][j]>255)
					p3[m][i][j]=255;
					else if(p3[m][i][j]<0)
					p3[m][i][j]=0;
				}
				
				
			}
		
	}
	
	cv::Mat convolution(orsize,ocsize,type);

 




	 cv::Mat image2(orsize,ocsize,type);
	 image2=imread("test.jpg",IMREAD_COLOR); 

	 Mat dst,kernel;
	 kernel=(Mat_<double>(3,3)<<1,2,1,2,4,2,1,2,1);
	 filter2D( image2, dst, -1 , kernel,Point(-1,-1),0,0);

	

	










	cv::Vec3b pixel=convolution.at<cv::Vec3b>(j,k);
	for(i=0;i<channel;i++)
	{
		for(j=0;j<orsize;j++)
		{
			for(k=0;k<ocsize;k++)
			{
				convolution.at<cv::Vec3b>(j,k)[i]=p3[i][j][k];
			}
		}
	}
	printf("%lf",sum);
	for(i=0;i<channel;i++)
	{
		for(j=0;j<orsize;j++)
		{
			for(k=0;k<ocsize;k++)
			{
				sum=sum+((dst.at<cv::Vec3b>(j,k)[i])-(convolution.at<cv::Vec3b>(j,k)[i]));
				
			}
		}
	}
	printf(" %lf\n\n\n  ",sum);
	
		
	imshow("convolution",dst-convolution);
	imwrite("compare.jpg",dst-convolution);
	
	


	for(i=0;i<channel;i++)//할당해제
	{
		for(j=0;j<orsize;j++)
		{
			
			free(*(*(p3+i)+j));
		}
		free(*(p3+i));
	}
	free(p3);
	
	
	
	for(i=0;i<channel;i++)//할당해제
	{
		for(j=0;j<f_size;j++)
		{
			
			free(*(*(p2+i)+j));
		}
		free(*(p2+i));
	}
	free(p2);


	for(i=0;i<channel;i++)//할당해제
	{
		for(j=0;j<bigr;j++)
		{
			
			free(*(*(p1+i)+j));
		}
		free(*(p1+i));
	}
	free(p1);

	



	
}

	


