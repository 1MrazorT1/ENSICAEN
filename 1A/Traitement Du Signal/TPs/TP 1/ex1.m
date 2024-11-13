A=[1 1 1; 2 1 1; 7 -5 -1];
B=[2;0;-6];
if det(A)~=0
    A_inv=inv(A);
    X=A_inv*B;
    disp('La solution du système est :');
    disp(X);
else
    disp('Ce système ne possède pas de solutions !')
end
