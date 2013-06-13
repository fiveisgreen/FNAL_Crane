//test if A and B are within 10^-scale of each other
bool aeq(float A, float B, int scale=5);

bool aeq(float A, float B, int scale){
        if(A>(B-pow(10,-1*scale)) && A<(B+pow(10,-1*scale))) return true;
        else return false;
}

inline bool safe==(float A, float B){ return A+0.0001>B && A-0.0001<B;}
inline bool safe==(double A, float B){ return A+0.0001>B && A-0.0001<B;}
inline bool safe==(float A, double B){ return A+0.0001>B && A-0.0001<B;}
inline bool safe==(double A, double B){ return A+0.0001>B && A-0.0001<B;}
