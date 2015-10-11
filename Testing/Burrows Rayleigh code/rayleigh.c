// Description: This program computes the Stokes parameters of
// reflected light for a semi-infinite atmosphere scattering in
// accordance with the Rayleigh phase matrix, for given orbital
// parameters and scattering albedo.
// -----------------------------------------------------------
// Code written by: N. Madhusudhan
// Code Usage:
// Compile: gcc rayleigh.c -lm
// Run:     ./a.out ws incl ecc argperi Omega
// ws = scattering albedo, incl = inclination in degrees
// ecc = eccentricity, argperi = argument of pericenter
// Omega = longitude of ascending node
// Example: ./a.out 1.0 15.0 0.5 90.0 90.0
// Output is file "fr.out" - contains the Stokes parameters
// for linear polarization (I, Q, U) as a function of the mean anomaly
//--------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

double PI = 3.14159265358979323846;
long Ngauss = 32;
double xgauss[40], wgauss[40], mu_g[40]; // Gauss points, weights, and mu array
#include "gauss.c" // includes Gauss weights and abscissae

double MMg[5][40], NNg[5][40], Ascat = 0.0, incl = 0.0; // = PI/3.0;// = 0.9;
void make_MMg(double [5][40]);
void setup_NNg();
void get_NN(double, double [], double []);

double IPsi1, IPsi2, IPsiV0, IPsiV1;
double Hg1[40], Hg2[40], HgV0[40], HgV1[40];

void Tweights(long, long, double *, double *);
double gauss_integral(double, double, double (*)(double), long);
double func_Psi1(double), func_Psi2(double), func_PsiV0(double), func_PsiV1(double);
void make_Hg(double, double (*)(double), double [], long);
double H_moment(long, double [], long);
void setup_Rayleigh_pol();
double get_H(double, double, double(*)(double), double [], long);
//double get_Ir(double, double, double);
double get_Ir(double, double, double, double []);
double get_Fr(double); 
double get_Frr(double, double []); 

double get_Ir_incl(double, double, double, double []);
double get_Frr_incl(double, double []); 

void setup_Hg();
double get_Ir_lambert(double, double, double);
double get_Fr_lambert(double); double get_lambert(double); 
double get_Ir_short(double, double, double, double []);

double get_alpha(double, double, double, double);
double get_EA(double, double);
#define rad2deg (180.0/PI)

main(int argc, char *argv[]) 
{
  if (argc != 6){printf("Insufficient arguments \n"); exit(EXIT_FAILURE);}
  Ascat = atof(argv[1]); 
  incl = atof(argv[2]); // input in degrees  
  
  double ecc, argperi, Omega;
  
  ecc = atof(argv[3]); 
  argperi = atof(argv[4]); // input in degrees  
  Omega = atof(argv[5]); // input in degrees
  
  printf("Ascat = %6.2f, incl = %6.2f, ecc = %6.2f, argperi = %6.2f, Omega = %6.2f\n",Ascat, incl, ecc, argperi, Omega); 
  
  incl *= PI/180.0; // convert to radians
  argperi *= PI/180.0; // convert to radians
  Omega *= PI/180.0; // convert to radians  
  
  setup_NNg();
  setup_Hg();
  
  double alp, alpha, Fr, Fr_lambert, Fr_arr[3]; long i;  
  
  FILE *fp;  double alpha_1, Qr, Ur, Qr1, Ur1, tan_gamma;
  fp = fopen("fr.out","w");  
  /*fprintf(fp,"%12s %12s %12s %12s %12s %12s\n","MA", "j/F",	\
    "Q/F", "U/F", "j/F(Rayl)", "j/F(Lmbrt)");  */
  fprintf(fp,"%12s %12s %12s %12s %12s\n","MA (deg)", "I/F",	\
	  "Q/F", "U/F", "I/F(Lmbrt)");  
  
  
  int N = 361; //, i; 
  double MA_arr[N], alp_arr[N], MA; //incl, alpha;
  double EA, cosTA, sinTA, sinf, cosf, cosw, sinw, gamma; //, Omega = PI/2.0;
  
  for(i=0;i<N;i++){
    MA = i*2.0*PI/(N-1); 
    EA = get_EA(MA,ecc);       //EA = Eccentric anomaly
    cosTA = (cos(EA)-ecc)/(1.0-ecc*cos(EA)); // TA = True anomaly
    sinTA = (1.0+ecc*cosTA)*sin(EA)/sqrt(1.0-ecc*ecc);    
    cosw = sinTA*cos(argperi) + cosTA*sin(argperi); //Note: f = TA + argperi
    sinw = -1.0*(cosTA*cos(argperi) - sinTA*sin(argperi)); 
    alpha_1 = asin(sqrt(cosw*cosw*cos(incl)*cos(incl) + sinw*sinw));
    if(cosw < 0.0){alpha_1 = PI - alpha_1;} // i.e. if 90 < w < 270    
    Fr = get_Frr(alpha_1, Fr_arr);
    Qr = Fr_arr[1]-Fr_arr[0]; Ur = Fr_arr[2];        
    
    gamma = atan2(sinw/cosw, cos(incl)) + PI/2.0 + Omega;
    tan_gamma = tan(gamma);
    
    Qr1 = ((1.0-tan_gamma*tan_gamma)/(1.0+tan_gamma*tan_gamma))*Qr;
    Ur1 = (-2.0*tan_gamma/(1.0+tan_gamma*tan_gamma))*Qr;    
    
    Fr_lambert = get_Fr_lambert(alpha_1);     
    /*fprintf(fp,"%12.1f %12.5f %12.5f %12.5f %12.5f %12.5f \n",	\
      MA*rad2deg,Fr_arr[0]+Fr_arr[1],Qr1, Ur1, Fr, Fr_lambert); */
    fprintf(fp,"%12.1f %12.5f %12.5f %12.5f %12.5f \n",			\
	    MA*rad2deg,Fr_arr[0]+Fr_arr[1],Qr1, Ur1, Fr_lambert); 
    //    printf("%12.1f %12.5f %12.5f %12.5f %12.5f %12.5f \n",	\
      //	   MA*rad2deg,Fr_arr[0]+Fr_arr[1],Qr1, Ur1, Fr, Fr_lambert); 
  } 
  close(fp);  
}

double get_alpha(double MA, double ecc, double incl, double argperi)
{
  double EA, cosTA, sinTA, sinf, cosf, MA_chk, TA_chk, alpha;
  int QQ;
  
  EA = get_EA(MA,ecc);       //EA = Eccentric anomaly
  cosTA = (cos(EA)-ecc)/(1.0-ecc*cos(EA)); // TA = True anomaly
  sinTA = (1.0+ecc*cosTA)*sin(EA)/sqrt(1.0-ecc*ecc);
  MA_chk = EA - ecc*sin(EA);
  sinf = sinTA*cos(argperi) + cosTA*sin(argperi); //Note: f = TA + argperi
  cosf = cosTA*cos(argperi) - sinTA*sin(argperi); 
  //alpha = acos(sinf);
  alpha = acos(sinf*sin(incl));  
  if((sinf >= 0.0)&&(cosf > 0.0)) QQ = 1 ;//first quadrant
  if((sinf >= 0.0)&&(cosf < 0.0)) QQ = 2 ;//second quadrant
  if((sinf < 0.0)&&(cosf <= 0.0)) QQ = 3 ;//third quadrant
  if((sinf < 0.0)&&(cosf >= 0.0)) QQ = 4 ;//fourth quadrant
  if((QQ == 1) || (QQ == 4)) alpha = 2.0*PI - alpha;
  TA_chk = acos(cosTA);
  //printf("%d %7.2F %7.2F %7.2F %7.2F %7.2F\n", QQ, MA*rad2deg, MA_chk*rad2deg, EA*rad2deg, TA_chk*rad2deg, alpha*rad2deg);
  //usleep(100000);
  return alpha;  
}

double get_EA(double MA, double ecc)
{
  int count; 
  double delta, EA, EA_prev;
  
  EA = MA; count = 0; delta = 1.0;
			
  while(delta >= 1.0E-10){
    EA_prev = EA;
    EA = MA + ecc*sin(EA);    
    delta = fabs((EA - EA_prev)/EA_prev);
    count++;
  } //MA_check = EA - ecc*sin(EA); print, ecc, MA, MA_check, EA, count;
  
  return EA;  
}


double get_Fr(double alpha) 
{  
  double Frx, x1, x2, w1, w2, sum, Irr[2];
  long ii, jj, n1, n2;
  
  sum = 0.0; n1 = 32, n2 = Ngauss;
  for(ii=1;ii<=n1;ii++){
    for(jj=1;jj<=n2;jj++){      
      Tweights(n1, ii, &x1, &w1);
      x2 = xgauss[jj]; w2 = wgauss[jj];
      sum = sum + w1*w2*get_Ir(alpha, x1,x2,Irr);
    }
  }
  
  Frx = 0.5*(cos(alpha)+1.0)*sum; 
  Frx = Frx/PI;
  
  return Frx;
}

double get_Frr(double alpha, double Frr[3]) 
{  
  double Frx, x1, x2, w1, w2, sum, Irr[3];
  double Ir, FrL, FrR, sumL, sumR, sumU, FrU;
  long ii, jj, n1, n2;
  
  //sum = 0.0; n1 = 32, n2 = Ngauss;
  sum = 0.0; sumL = 0.0; sumR = 0.0; n1 = Ngauss; n2 = Ngauss;
  sumU = 0.0;
  for(ii=1;ii<=n1;ii++){
    for(jj=1;jj<=n2;jj++){      
      Tweights(n1, ii, &x1, &w1);
      x2 = xgauss[jj]; w2 = wgauss[jj];
      Ir = get_Ir(alpha, x1,x2,Irr); sum += w1*w2*Ir;
      sumL += w1*w2*Irr[0]; sumR += w1*w2*Irr[1];
      sumU += w1*w2*Irr[2];
    }
  }
  
  Frx = 0.5*(cos(alpha)+1.0)*sum/PI;   
  FrL = 0.5*(cos(alpha)+1.0)*sumL/PI; 
  FrR = 0.5*(cos(alpha)+1.0)*sumR/PI; 
  FrU = 0.5*(cos(alpha)+1.0)*sumU/PI; 

  Frr[0] = FrL; Frr[1] = FrR; Frr[2] = FrU; 

  return Frx;
}

double get_Frr_incl(double alpha, double Frr[3]) 
{  
  double Frx, x1, x2, w1, w2, sum, Irr[3];
  double Ir, FrL, FrR, sumL, sumR, sumU, FrU;
  long ii, jj, n1, n2;
  
  //sum = 0.0; n1 = 32, n2 = Ngauss;
  sum = 0.0; sumL = 0.0; sumR = 0.0; n1 = Ngauss; n2 = Ngauss;
  sumU = 0.0;
  for(ii=1;ii<=n1;ii++){
    for(jj=1;jj<=n2;jj++){      
      //Tweights(n1, ii, &x1, &w1);
      x1 = xgauss[ii]; w1 = wgauss[ii];
      x2 = xgauss[jj]; w2 = wgauss[jj];
      Ir = get_Ir_incl(alpha, x1,x2,Irr); sum += w1*w2*Ir;
      sumL += w1*w2*Irr[0]; sumR += w1*w2*Irr[1];
      sumU += w1*w2*Irr[2];
    }
  }
  
  //printf("%f %f \n", incl, (sin(incl)+1.0));
  Frx = 0.25*(cos(alpha)+1.0)*(sin(incl)+1.0)*sum/PI;   
  FrL = 0.25*(cos(alpha)+1.0)*(sin(incl)+1.0)*sumL/PI; 
  FrR = 0.25*(cos(alpha)+1.0)*(sin(incl)+1.0)*sumR/PI; 
  FrU = 0.25*(cos(alpha)+1.0)*(sin(incl)+1.0)*sumU/PI; 

  Frr[0] = FrL; Frr[1] = FrR; Frr[2] = FrU; 

  return Frx;
}

//double get_Ir_short(double phi, double theta_0, double theta, double Irr[2]) // Function to calculate I/F
double get_Ir_short(double phi, double mu_0, double mu, double Irr[2]) // Function to calculate I/F
{
  //  double nu=0.0, xx=0.0, mu0=0.0, Ir=0.0, mu_0=0.0, mu_1 = 0.0, mu=0.0, sin_phi=0.0, cos_phi=0.0;
  double Ir=0.0, sin_phi=0.0, cos_phi=0.0;
  double Hmu1, Hmu2, HmuV0, HmuV1, Fpsi, Fphi, Fxi, Feta;
  double Hmu1_0, Hmu2_0, HmuV0_0, HmuV1_0, Fpsi_0, Fphi_0, Fxi_0, Feta_0; 
  double IrL, IrR, Ur, Vr;
  
  /*  nu = 0.5*(cos(alpha)+1.0)*(x2 - (cos(alpha)-1.0)/(cos(alpha)+1.0));
      xx = cos(alpha)*sqrt(1.0-nu*nu) + sin(alpha)*nu;
      mu0 = sqrt(1.0-x1*x1)*xx;  
      mu_1 = sqrt(1.0-x1*x1)*sqrt(1.0-nu*nu);  
      sin_phi = sin(alpha)*x1/sqrt((1.0-mu_1*mu_1)*(1.0-mu0*mu0));  
      cos_phi = (mu_1*mu0 - cos(alpha))/sqrt((1.0-mu_1*mu_1)*(1.0-mu0*mu0)); //chk2 = cos_phi;
      //mu_0 = mu0; mu = mu_1;
  */
  
  //  mu_0 = cos(theta_0*PI/180.0);
  //  mu = cos(theta*PI/180.0);
  sin_phi = sin(phi*PI/180.0);
  cos_phi = cos(phi*PI/180.0);  
  
  Hmu1_0 = get_H(mu_0,IPsi1,&func_Psi1,Hg1,Ngauss);    
  Hmu2_0 = get_H(mu_0,IPsi2,&func_Psi2,Hg2,Ngauss);
  HmuV0_0 = get_H(mu_0,IPsiV0,&func_PsiV0,HgV0,Ngauss);
  HmuV1_0 = get_H(mu_0,IPsiV1,&func_PsiV1,HgV1,Ngauss);
  
  //printf("%f %f %f \n",mu_0,Hmu1_0,Hmu2_0);  
  //exit(1);
  
  Hmu1 = get_H(mu,IPsi1,&func_Psi1,Hg1,Ngauss);    
  Hmu2 = get_H(mu,IPsi2,&func_Psi2,Hg2,Ngauss);
  HmuV0 = get_H(mu,IPsiV0,&func_PsiV0,HgV0,Ngauss);
  HmuV1 = get_H(mu,IPsiV1,&func_PsiV1,HgV1,Ngauss);
  
  //printf("%f %f %f \n",mu,Hmu1,Hmu2);

  double NN_0[5], NN[5], MM_0[5], MM[5];
  
  get_NN(mu_0, NN_0, MM_0); // MM is just for reference
  get_NN(mu, NN, MM);
  
  double Al, Ar, Bl, Bu, Cl, Cu, Cr, D;
  
  Al = NN[1]*(NN_0[1] + NN_0[3]) +  NN[2]*(NN_0[2] + NN_0[4]);
  Ar = NN[3]*(NN_0[1] + NN_0[3]) +  NN[4]*(NN_0[2] + NN_0[4]);

  Bu = 3.0*mu_0*sqrt(1.0-mu*mu)*sqrt(1.0-mu_0*mu_0)*Hmu1*Hmu1_0;
  Bl = -1.0*mu*Bu;

  Cr = 0.75*(1.0-mu_0*mu_0)*Hmu2*Hmu2_0;
  Cl = -1.0*mu*mu*Cr;
  Cu = 2.0*mu*Cr;

  D = 1.0/(8.0*(mu + mu_0));
  
  IrL = Ascat*D*(Al + Bl*cos_phi + Cl*(2.0*cos_phi*cos_phi - 1.0))*mu_0;
  IrR = Ascat*D*(Ar + Cr*(2.0*cos_phi*cos_phi - 1.0))*mu_0; 
  
  Ur = 1.0*Ascat*D*(Bu*sin_phi + Cu*2.0*sin_phi*cos_phi)*mu_0; // -1 is because of (phi_0 - phi)
  Vr = 0.0;
  
  //printf("%f %f %f %f %f %f %f\n", mu_0, mu, Hmu1_0, Hmu2_0,Hmu1, Hmu2, IrL/mu_0) ;
  //printf("%f %f %f %f %f %f\n", mu_0, NN_0[1], NN_0[2], NN_0[3], NN_0[4], IrL/mu_0) ;
  //printf("%f %f %f %f %f %f\n", mu, NN[1], NN[2], NN[3], NN[4], IrL/mu_0);
  
  //  usleep(100000);
  //Ir = 3.0/32.0*mu_0/(mu_0+mu_1)*(xi_1*xi_0/3.0 + phi_1*phi_0*8.0/3.0  - (2.0*mu_1*sqrt(1.0-mu_1*mu_1)*Hmu1*2.0*mu_0*sqrt(1.0-mu_0*mu_0)*Hmu1_0)*cos_phi + (1.0 - mu_1*mu_1)*Hmu2*(1.0 - mu_0*mu_0)*Hmu2_0*(2.0*cos_phi*cos_phi - 1.0));

  Irr[0] = IrL; Irr[1] = IrR; 
  
  Ir = IrL + IrR;
  
  //Ir = sqrt(IrL*IrL + IrR*IrR);

  return Ir;  
}

double get_Ir_incl(double alpha, double x1, double x2, double Irr[3]) // Function to calculate I/F
{
  double nu=0.0, psi=0.0, Ir=0.0, mu_0=0.0, mu_1 = 0.0, mu=0.0, sin_phi=0.0, cos_phi=0.0;
  double Hmu1, Hmu2, HmuV0, HmuV1, Fpsi, Fphi, Fxi, Feta;
  double Hmu1_0, Hmu2_0, HmuV0_0, HmuV1_0, Fpsi_0, Fphi_0, Fxi_0, Feta_0; 
  double IrL, IrR, Ur, Vr;
  
  psi = 0.5*(1.0+sin(incl))*x1 + 0.5*(1.0-sin(incl));
  nu = 0.5*(1.0+cos(alpha))*x2 + 0.5*(1.0-cos(alpha));
  mu_0 = sqrt(1.0-psi*psi)*(cos(alpha)*sqrt(1.0-nu*nu) + sin(alpha)*nu);  
  mu_1 = sqrt(1.0-psi*psi)*sqrt(1.0-nu*nu);  
  sin_phi = sin(alpha)*psi/sqrt((1.0-mu_1*mu_1)*(1.0-mu_0*mu_0));  
  cos_phi = (mu_1*mu_0 - cos(alpha))/sqrt((1.0-mu_1*mu_1)*(1.0-mu_0*mu_0)); //chk2 = cos_phi;
  
  mu = mu_1;
  Hmu1_0 = get_H(mu_0,IPsi1,&func_Psi1,Hg1,Ngauss);    
  Hmu2_0 = get_H(mu_0,IPsi2,&func_Psi2,Hg2,Ngauss);
  HmuV0_0 = get_H(mu_0,IPsiV0,&func_PsiV0,HgV0,Ngauss);
  HmuV1_0 = get_H(mu_0,IPsiV1,&func_PsiV1,HgV1,Ngauss);
  
  Hmu1 = get_H(mu,IPsi1,&func_Psi1,Hg1,Ngauss);    
  Hmu2 = get_H(mu,IPsi2,&func_Psi2,Hg2,Ngauss);
  HmuV0 = get_H(mu,IPsiV0,&func_PsiV0,HgV0,Ngauss);
  HmuV1 = get_H(mu,IPsiV1,&func_PsiV1,HgV1,Ngauss);
  
  double NN_0[5], NN[5], MM[5];
  
  get_NN(mu_0, NN_0, MM); // MM is just for reference
  get_NN(mu, NN, MM);
  
  double Al, Ar, Bl, Bu, Cl, Cu, Cr, D;
  
  Al = NN[1]*(NN_0[1] + NN_0[3]) +  NN[2]*(NN_0[2] + NN_0[4]);
  Ar = NN[3]*(NN_0[1] + NN_0[3]) +  NN[4]*(NN_0[2] + NN_0[4]);

  Bu = 3.0*mu_0*sqrt(1.0-mu*mu)*sqrt(1.0-mu_0*mu_0)*Hmu1*Hmu1_0;
  Bl = -1.0*mu*Bu;

  Cr = 0.75*(1.0-mu_0*mu_0)*Hmu2*Hmu2_0;
  Cl = -1.0*mu*mu*Cr;
  Cu = 2.0*mu*Cr;

  D = 1.0/(8.0*(mu + mu_0));
    
  IrL = Ascat*D*(Al + Bl*cos_phi + Cl*(2.0*cos_phi*cos_phi - 1.0))*mu_0;
  IrR = Ascat*D*(Ar + Cr*(2.0*cos_phi*cos_phi - 1.0))*mu_0; 
  
  Ur = -1.0*Ascat*D*(Bu*sin_phi + Cu*2.0*sin_phi*cos_phi)*mu_0; // -1 is because of (phi_0 - phi)
  Vr = 0.0;

  //Irr[0] = IrL; Irr[1] = IrR;  Ir = IrL + IrR;
  
  // Rotation of Stokes vector ------------------------------------  
  double cos_rot, sin_rot, cos2rot, sin2rot, Ir0, Qr0, Ur0, Vr0;
  double Ir_1, Qr_1, Ur_1, Vr_1, IrL_1, IrR_1;
  
  cos_rot = sqrt(1.0-x1*x1)*nu/sqrt(1.0-mu_1*mu_1);
  sin_rot = x1/sqrt(1.0-mu_1*mu_1);
  
  cos2rot = (2.0*cos_rot*cos_rot - 1.0);
  sin2rot = 2.0*sin_rot*cos_rot;
  
  Ir0 = IrL + IrR; Qr0 = IrL - IrR; Ur0 = Ur; Vr0 = Vr;
  
  Ir_1 = Ir0;
  Qr_1 = Qr0*cos2rot + Ur0*sin2rot;
  Ur_1 = -Qr0*sin2rot + Ur0*cos2rot;
  Vr_1 = Vr0;
  
  IrL_1 = (Ir_1 + Qr_1)/2.0; IrR_1 = (Ir_1 - Qr_1)/2.0; 	  
  //--------------------------------------------------------------
  
  //Second Rotation
  double Qr_2, Ur_2;
  
  Qr_2 = Qr_1*cos(2.0*incl) + Ur_1*sin(2.0*incl);
  Ur_2 = -Qr_1*sin(2.0*incl) + Ur_1*cos(2.0*incl);

  Qr_1 = Qr_2; Ur_1 = Ur_2;
  
  IrL_1 = (Ir_1 + Qr_1)/2.0; IrR_1 = (Ir_1 - Qr_1)/2.0; 	  
  //---------------------------------------------------------

  //  Irr[0] = IrL_1; Irr[1] = IrR_1; Irr[2] = Ur_1; Ir = IrL_1 + IrR_1;
  
  double xfac = 0.0;
  xfac = sin(incl)*sqrt(1.0-psi*psi) + psi*cos(incl)/sqrt(1.0 - nu*nu);
  
  Irr[0] = IrL_1*xfac; Irr[1] = IrR_1*xfac; Irr[2] = Ur_1*xfac;  
  Ir = (IrL_1 + IrR_1)*xfac;

  return Ir;  
}

double get_Ir(double alpha, double x1, double x2, double Irr[3]) // Function to calculate I/F
{
  double nu=0.0, xx=0.0, mu0=0.0, Ir=0.0, mu_0=0.0, mu_1 = 0.0, mu=0.0, sin_phi=0.0, cos_phi=0.0;
  double Hmu1, Hmu2, HmuV0, HmuV1, Fpsi, Fphi, Fxi, Feta;
  double Hmu1_0, Hmu2_0, HmuV0_0, HmuV1_0, Fpsi_0, Fphi_0, Fxi_0, Feta_0; 
  double IrL, IrR, Ur, Vr;
  
  nu = 0.5*(cos(alpha)+1.0)*(x2 - (cos(alpha)-1.0)/(cos(alpha)+1.0));
  xx = cos(alpha)*sqrt(1.0-nu*nu) + sin(alpha)*nu;
  mu0 = sqrt(1.0-x1*x1)*xx;  
  mu_1 = sqrt(1.0-x1*x1)*sqrt(1.0-nu*nu);  
  sin_phi = sin(alpha)*x1/sqrt((1.0-mu_1*mu_1)*(1.0-mu0*mu0));  
  cos_phi = (mu_1*mu0 - cos(alpha))/sqrt((1.0-mu_1*mu_1)*(1.0-mu0*mu0)); //chk2 = cos_phi;
  
  mu_0 = mu0; mu = mu_1;
  Hmu1_0 = get_H(mu_0,IPsi1,&func_Psi1,Hg1,Ngauss);    
  Hmu2_0 = get_H(mu_0,IPsi2,&func_Psi2,Hg2,Ngauss);
  HmuV0_0 = get_H(mu_0,IPsiV0,&func_PsiV0,HgV0,Ngauss);
  HmuV1_0 = get_H(mu_0,IPsiV1,&func_PsiV1,HgV1,Ngauss);
  
  Hmu1 = get_H(mu,IPsi1,&func_Psi1,Hg1,Ngauss);    
  Hmu2 = get_H(mu,IPsi2,&func_Psi2,Hg2,Ngauss);
  HmuV0 = get_H(mu,IPsiV0,&func_PsiV0,HgV0,Ngauss);
  HmuV1 = get_H(mu,IPsiV1,&func_PsiV1,HgV1,Ngauss);
  
  double NN_0[5], NN[5], MM[5];
  
  get_NN(mu_0, NN_0, MM); // MM is just for reference
  get_NN(mu, NN, MM);
  
  double Al, Ar, Bl, Bu, Cl, Cu, Cr, D;
  
  Al = NN[1]*(NN_0[1] + NN_0[3]) +  NN[2]*(NN_0[2] + NN_0[4]);
  Ar = NN[3]*(NN_0[1] + NN_0[3]) +  NN[4]*(NN_0[2] + NN_0[4]);

  Bu = 3.0*mu_0*sqrt(1.0-mu*mu)*sqrt(1.0-mu_0*mu_0)*Hmu1*Hmu1_0;
  Bl = -1.0*mu*Bu;

  Cr = 0.75*(1.0-mu_0*mu_0)*Hmu2*Hmu2_0;
  Cl = -1.0*mu*mu*Cr;
  Cu = 2.0*mu*Cr;

  D = 1.0/(8.0*(mu + mu_0));
    
  IrL = Ascat*D*(Al + Bl*cos_phi + Cl*(2.0*cos_phi*cos_phi - 1.0))*mu_0;
  IrR = Ascat*D*(Ar + Cr*(2.0*cos_phi*cos_phi - 1.0))*mu_0; 
  
  Ur = -1.0*Ascat*D*(Bu*sin_phi + Cu*2.0*sin_phi*cos_phi)*mu_0; // -1 is because of (phi_0 - phi)
  Vr = 0.0;

  //Irr[0] = IrL; Irr[1] = IrR;  Ir = IrL + IrR;
  
  // Rotation of Stokes vector ------------------------------------  
  double cos_rot, sin_rot, cos2rot, sin2rot, Ir0, Qr0, Ur0, Vr0;
  double Ir_1, Qr_1, Ur_1, Vr_1, IrL_1, IrR_1;
  
  cos_rot = sqrt(1.0-x1*x1)*nu/sqrt(1.0-mu_1*mu_1);
  sin_rot = x1/sqrt(1.0-mu_1*mu_1);
  
  cos2rot = (2.0*cos_rot*cos_rot - 1.0);
  sin2rot = 2.0*sin_rot*cos_rot;
  
  Ir0 = IrL + IrR; Qr0 = IrL - IrR; Ur0 = Ur; Vr0 = Vr;
  
  Ir_1 = Ir0;
  Qr_1 = Qr0*cos2rot + Ur0*sin2rot;
  Ur_1 = -Qr0*sin2rot + Ur0*cos2rot;
  Vr_1 = Vr0;
  
  IrL_1 = (Ir_1 + Qr_1)/2.0; IrR_1 = (Ir_1 - Qr_1)/2.0; 	  
  //--------------------------------------------------------------
  
  Irr[0] = IrL_1; Irr[1] = IrR_1;  Ir = IrL_1 + IrR_1;
  
  Irr[2] = Ur_1;

  return Ir;  
}

void setup_Hg()
{
  IPsi1 = gauss_integral(0.0,1.0,&func_Psi1,Ngauss); 
  IPsi2 = gauss_integral(0.0,1.0,&func_Psi2,Ngauss); 
  IPsiV0 = gauss_integral(0.0,1.0,&func_PsiV0,Ngauss); 
  IPsiV1 = gauss_integral(0.0,1.0,&func_PsiV1,Ngauss); 
  
  make_Hg(IPsi1, &func_Psi1, Hg1, Ngauss); 
  make_Hg(IPsi2, &func_Psi2, Hg2, Ngauss); 
  make_Hg(IPsiV0, &func_PsiV0, HgV0, Ngauss); 
  make_Hg(IPsiV1, &func_PsiV1, HgV1, Ngauss); 
}

void get_NN(double xmu, double NNx[5], double MMx[5])
{
  double mup, sum[5], AA; int j, k;
  
  MMx[1] = (sqrt(3.0)/2.0)*xmu*xmu;
  MMx[2] = sqrt(3.0/2.0)*(1.0-xmu*xmu);
  MMx[3] = sqrt(3.0)/2.0;
  MMx[4] = 0.0;
  
  for(j=1;j<=4;j++){sum[j] = 0.0;}
  for(k=1;k<=Ngauss;k++){
    mup = mu_g[k];
    sum[1] = sum[1] + (wgauss[k]/2.0)*(NNg[1][k]*MMg[1][k] + NNg[3][k]*MMg[3][k])/(xmu+mup);
    sum[2] = sum[2] + (wgauss[k]/2.0)*(NNg[1][k]*MMg[2][k] + NNg[3][k]*MMg[4][k])/(xmu+mup);
    sum[3] = sum[3] + (wgauss[k]/2.0)*(NNg[2][k]*MMg[1][k] + NNg[4][k]*MMg[3][k])/(xmu+mup);
    sum[4] = sum[4] + (wgauss[k]/2.0)*(NNg[2][k]*MMg[2][k] + NNg[4][k]*MMg[4][k])/(xmu+mup);
  }
  
  AA = 0.5*Ascat*xmu;
  NNx[1] = (MMx[1]*(1.0-AA*sum[4]) + MMx[2]*AA*sum[3])/((1.0-AA*sum[4])*(1.0-AA*sum[1]) \
								 - AA*AA*sum[2]*sum[3]); 
  NNx[2] = (MMx[2] + AA*sum[2]*NNx[1])/(1.0-AA*sum[4]);  
  
  NNx[3] = (MMx[3]*(1.0-AA*sum[4]) + MMx[4]*AA*sum[3])/((1.0-AA*sum[4])*(1.0-AA*sum[1]) \
								 - AA*AA*sum[2]*sum[3]); 
  NNx[4] = (MMx[4] + AA*sum[2]*NNx[3])/(1.0-AA*sum[4]);      
}

void setup_NNg()
{
  //double MMg[5][40], NNg[5][40]; // made global now
  double NNg_old[5][40], sum[5], AA;
  double mu, mup, eps0, eps, err;
  int i, j, k, count;
  //double Ascat = 1.0; // made global now

  gauss(Ngauss);  
  for(i=1;i<=Ngauss;i++){mu_g[i] = (xgauss[i] + 1.0)/2.0;}
  make_MMg(MMg);
  
  for(i=1;i<=4;i++){for(j=1;j<=Ngauss;j++){NNg[i][j]=MMg[i][j];}} //initialize  
  //for(i=1;i<=4;i++){for(j=1;j<=Ngauss;j++){NNg[i][j]=1.0;}} //initialize  
  err = 1.0; count = 0; 
  while(err > 1.0E-9){count++;
    for(i=1;i<=4;i++){for(j=1;j<=Ngauss;j++){NNg_old[i][j]=NNg[i][j];}}
    for(i=1;i<=Ngauss;i++){
      mu = mu_g[i]; for(j=1;j<=4;j++){sum[j] = 0.0;}        
      for(k=1;k<=Ngauss;k++){
	mup = mu_g[k];
	sum[1] = sum[1] + (wgauss[k]/2.0)*(NNg[1][k]*MMg[1][k] + NNg[3][k]*MMg[3][k])/(mu+mup);
	sum[2] = sum[2] + (wgauss[k]/2.0)*(NNg[1][k]*MMg[2][k] + NNg[3][k]*MMg[4][k])/(mu+mup);
	sum[3] = sum[3] + (wgauss[k]/2.0)*(NNg[2][k]*MMg[1][k] + NNg[4][k]*MMg[3][k])/(mu+mup);
	sum[4] = sum[4] + (wgauss[k]/2.0)*(NNg[2][k]*MMg[2][k] + NNg[4][k]*MMg[4][k])/(mu+mup);
      }
      AA = 0.5*Ascat*mu;

      NNg[1][i] = (MMg[1][i]*(1.0-AA*sum[4]) + MMg[2][i]*AA*sum[3])/((1.0-AA*sum[4])*(1.0-AA*sum[1]) \
								     - AA*AA*sum[2]*sum[3]); 
      NNg[2][i] = (MMg[2][i] + AA*sum[2]*NNg[1][i])/(1.0-AA*sum[4]);  
      
      NNg[3][i] = (MMg[3][i]*(1.0-AA*sum[4]) + MMg[4][i]*AA*sum[3])/((1.0-AA*sum[4])*(1.0-AA*sum[1]) \
								     - AA*AA*sum[2]*sum[3]); 
      NNg[4][i] = (MMg[4][i] + AA*sum[2]*NNg[3][i])/(1.0-AA*sum[4]);         
    }
    eps0 = 0.0;
    for(i=1;i<=4;i++){for(j=1;j<=Ngauss;j++){
	eps = fabs((NNg[i][j] - NNg_old[i][j])/NNg_old[i][j]);
	if(eps > eps0){eps0 = eps;}
      }}
    err = eps0;
  } //printf("Convergence achieved: count = %d, err = %e \n",count,err);
  
  //puts("Values at Gauss points:");
  //printf("%10s %10s %10s %10s %10s \n","mu","N1","N2","N3","N4");
  //  for(j=1;j<=Ngauss;j=j+1){
  //  printf("%10f %10f %10f %10f %10f \n",mu_g[j],NNg[1][j],NNg[2][j],NNg[3][j],NNg[4][j]);}
  //    printf("%10f %10f %10f %10f %10f \n",mu_g[j],MMg[1][j],MMg[2][j],MMg[3][j],MMg[4][j]);}
}

void make_MMg(double MMg[5][40])
{
  int i1; double xmu; 
  for(i1=1;i1<=Ngauss;i1++){
    xmu = mu_g[i1];
    MMg[1][i1] = (sqrt(3.0)/2.0)*xmu*xmu;
    MMg[2][i1] = sqrt(3.0/2.0)*(1.0-xmu*xmu);
    MMg[3][i1] = sqrt(3.0)/2.0;
    MMg[4][i1] = 0.0;
  }
}

double H_moment(long nm, double Hg[], long Ngauss)
{
  long i; double sum;
  sum = 0.0;
  for(i=1; i<=Ngauss; i++){ sum += pow(mu_g[i],nm)*Hg[i]*wgauss[i]*1.0/2.0;}
  return sum;
}

double get_H(double mu, double IPsi, double(*func_Psi)(double), double Hg[], long Ngauss)
{ long j;  double xx1, fx, Psi_x, sum, Hinv, Hmu;  
  sum = 0.0;
  for(j=1;j<=Ngauss;j++){    
    xx1 = mu_g[j]; Psi_x = (*func_Psi)(xx1);
    fx = xx1*Psi_x*Hg[j]/(mu+xx1);    
    sum += wgauss[j]*fx*1.0/2.0;    
  }
  Hinv = sqrt(1.0 - 2.0*IPsi) + sum; Hmu = 1.0/Hinv;
  return Hmu;
}

void make_Hg(double IPsi, double (*func_Psi)(double), double Hg[], long Ngauss) // check Hg passing
{
  long i, j, k;
  double mu, xx1, Psi_x, fx, sum, Hinv, eps0, eps;
  double HH[40], HH_old[40]; //puts("Here");
  
  for(i=1;i<=Ngauss;i++){HH[i]=1.0;}    
  for(j=1;j<30;j++){
    for(i=1;i<=Ngauss;i++){HH_old[i]=HH[i];}    
    for(i=1;i<=Ngauss;i++){
      sum = 0.0; mu = mu_g[i];
      for(k=1;k<=Ngauss;k++){
	xx1 = mu_g[k]; Psi_x = (*func_Psi)(xx1);
	fx = xx1*Psi_x*HH[k]/(mu+xx1);
	sum += wgauss[k]*fx*(1.0/2.0); // (1/2) = (1.0-0.0)/(1-(-1))
      }
      Hinv = sqrt(1.0 - 2.0*IPsi) + sum; HH[i] = 1.0/Hinv; 
    }
    eps0 = 0.0;
    for(i=1;i<=Ngauss;i++){eps = fabs(HH[i]-HH_old[i])/HH_old[i]; 
      if(eps > eps0){eps0 = eps;}
    } //printf("%d %e \n",j, eps0);
    if(eps0 < 1.0E-9) break;
  }
  for(i=1;i<=Ngauss;i++){Hg[i]=HH[i];}
}

double func_Psi1(double x){double Psi; 
  Psi = (3.0/8.0)*Ascat*(1.0-x*x)*(1.0+2.0*x*x);
  return Psi;}

double func_Psi2(double x){double Psi; 
  Psi = (3.0/16.0)*Ascat*(1.0+x*x)*(1.0+x*x);
  return Psi;}

double func_PsiV0(double x){double Psi; 
  Psi = (3.0/4.0)*Ascat*x*x;
  return Psi;}

double func_PsiV1(double x){double Psi; 
  Psi = (3.0/8.0)*Ascat*(1.0-x*x);
  return Psi;}

double gauss_integral(double x1, double x2, double (*myfunc)(double), long Ngauss)
{ //puts("Inside Gauss Integral");
  double xg, xx1, fx, sum;
  long j;  
  sum = 0.0;  
  for(j=1;j<=Ngauss;j++){
    xg = xgauss[j];
    xx1 = (xg + 1.0)*(x2-x1)/2.0 + x1;
    fx = (*myfunc)(xx1);
    sum += wgauss[j]*fx*(x2-x1)/2.0;    
  }
  return sum;
}

void Tweights(long nquad, long i, double *xxi, double *wwi)
{
  *xxi = cos(i*PI/(nquad+1.0));
  *wwi = (PI/(nquad + 1.0))*sin(i*PI/(nquad + 1.0))*sin(i*PI/(nquad + 1.0));  
}


double get_Ir_lambert(double alpha, double x1, double x2) // Function to calculate I/F
{
  double nu=0.0, xx=0.0, mu0=0.0, Ir=0.0, mu_1=0.0, sin_phi=0.0, cos_phi=0.0;
  double Hmu, Hmu0, Hmu1, Hmu2, xi, phi;
  double mu_0, Hmu0_0, Hmu1_0, Hmu2_0, xi_0, phi_0; 
  //long Ngauss = 32;
  
  nu = 0.5*(cos(alpha)+1.0)*(x2 - (cos(alpha)-1.0)/(cos(alpha)+1.0));
  xx = cos(alpha)*sqrt(1.0-nu*nu) + sin(alpha)*nu;
  mu0 = sqrt(1.0-x1*x1)*xx;  
  mu_1 = sqrt(1.0-x1*x1)*sqrt(1.0-nu*nu);  
  sin_phi = sin(alpha)*x1/sqrt((1.0-mu_1*mu_1)*(1.0-mu0*mu0));
  cos_phi = sqrt(1.0 - sin_phi*sin_phi);
  
  //double Ascat = 1.0;
  Ir = 1.0*Ascat*mu0;
  
  return Ir;  
}

double get_Fr_lambert(double alpha) 
{  
  double Frx, x1, x2, w1, w2, sum, Ir_1;
  long ii, jj, n1, n2;
  
  sum = 0.0; n1 = 32, n2 = Ngauss;
  for(ii=1;ii<=n1;ii++){
    for(jj=1;jj<=n2;jj++){      
      Tweights(n1, ii, &x1, &w1);
      x2 = xgauss[jj]; w2 = wgauss[jj];
      sum = sum + w1*w2*get_Ir_lambert(alpha, x1,x2);
    }
  }
  
  Frx = 0.5*(cos(alpha)+1.0)*sum; 
  Frx = Frx/PI;
  
  return Frx;
}

double get_lambert(double alpha) 
{
  double fr_lambert;
  
  fr_lambert = (2.0/3.0)*((PI-alpha)*cos(alpha) + sin(alpha));  
  fr_lambert = fr_lambert/PI;
  
  return fr_lambert;
}
