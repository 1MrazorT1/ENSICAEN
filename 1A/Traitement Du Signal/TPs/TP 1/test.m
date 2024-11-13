%% Correction du BE sur la transformée de Forurier discrète
% Partie I : sig1_rect.mat

clearvars
close all
clc

load données/sig1_rect.mat
Ts = 1/Fs;
N=length(xk);
Ta = N*Ts;
% Etalonnage temporel
t = 0:Ts:Ta-Ts;

% Etalonnage fréquentiel :
f = 0:1/Ta:Fs-1/Ta;
f1 = -Fs/2:1/Ta:Fs/2-1/Ta;
subplot(411)
stem(t,xk,'dk','LineWidth',2)
xlabel('Temps (s)')
ylabel('x')
grid minor
legend('Signal temporel')

subplot(412)
stem(f1,fftshift(abs(fft(xk))),'dk','LineWidth',2)
xlabel('Fréquence ( Hz)')
ylabel('|X(f)|')
legend('Spectre de x(t)')
grid minor
axis([-Fs/2 Fs/2 0 max(abs(fft(xk)))])


% Durée du signal rectangle est :
T0 = 20*Ts;   % 1/T0 = 409.6 Hz

% Précision fréquentielle : 1/Ta

% Amilioration de la précision fréquentielle : Zero Padding
M=100;
xzp = [xk zeros(1,N*M)];
Nzp = length(xzp);
Ta1 = Nzp*Ts;
t1=0:Ts:Ta1-Ts;
fzp = -Fs/2:1/Ta1:Fs/2-1/Ta1;

subplot(413)
stem(t1,xzp,'dk','LineWidth',2)
xlabel('Temps (s)')
ylabel('xzp')
grid minor
legend('Signal temporel')


subplot(414)
stem(fzp,fftshift(abs(fft(xzp))),'dk','LineWidth',2)
xlabel('Fréquence ( Hz)')
ylabel('|X(f)|')
legend('Spectre de xzp(t)')
grid minor
axis([-Fs/2 Fs/2 0 max(abs(fft(xzp)))])

%% Partie II : sig1_quidonc.mat
clearvars
close all
clc

load données/sig2_quidonc.mat   % modifier sig2_quidonc.mat  sig3_quidonc.mat

Ts = 1/Fs;
N=length(xk);
Ta = N*Ts;
% Etalonnage temporel
t = 0:Ts:Ta-Ts;

% Etalonnage fréquentiel :
f = 0:1/Ta:Fs-1/Ta;
f1 = -Fs/2:1/Ta:Fs/2-1/Ta;
subplot(511)
stem(t,xk,'dk','LineWidth',2)
xlabel('Temps (s)')
ylabel('x')
grid minor
legend('Signal temporel')

subplot(512)
stem(f1,fftshift(abs(fft(xk))),'dk','LineWidth',2)
xlabel('Fréquence ( Hz)')
ylabel('|X(f)|')
legend('Spectre de x(t)')
grid minor
axis([-Fs/2 Fs/2 0 max(abs(fft(xk)))])

% Application de la fenêtre de Hamming
Fen = hamming(N);
xfen = xk.*Fen.';
subplot(513)
stem(t,xfen,'dr','LineWidth',2)
xlabel('Temps (s)')
ylabel('x')
grid minor
legend('Signal temporel fenêtré')

% + Zero Padding

M=100;
xzp = [xfen zeros(1,N*M)];
Nzp = length(xzp);
Ta1 = Nzp*Ts;
t1=0:Ts:Ta1-Ts;
fzp = -Fs/2:1/Ta1:Fs/2-1/Ta1;

subplot(514)
stem(t1,xzp,'dk','LineWidth',2)
xlabel('Temps (s)')
ylabel('xzp')
grid minor
legend('Signal temporel')


subplot(515)
stem(fzp,fftshift(abs(fft(xzp))),'dk','LineWidth',2)
xlabel('Fréquence ( Hz)')
ylabel('|X(f)|')
legend('Spectre de xzp(t)')
grid minor
axis([-Fs/2 Fs/2 0 max(abs(fft(xzp)))])

%% Reconstitution du signal

figure
f1= 0:1/Ta1:Fs-1/Ta1;
Xzp = abs(fft(xzp));
Xzpn= Xzp/max(Xzp);
stem(f1,Xzpn,'.k','LineWidth',2)
xlabel('Fréquence (Hz)')
ylabel('|X|')
legend('Sepectre de xzp')
grid minor
% Findpeaks (les maximas de cette fonction)


[peaks,inds]=findpeaks(Xzpn,'MinpeakHeight',0.1); %Le seuil est choisi par rapport à la fenêtre utilisée

hold on
plot(f1(inds),peaks,'dr','LineWidth',3)

ff=f1(inds);
freq = ff(1:4);
ampl = peaks(1:4)

xrec = ampl(1)*sin(2*pi*t*ff(1))+ampl(2)*sin(2*pi*t*ff(2))+ampl(3)*sin(2*pi*t*ff(3))+ampl(4)*sin(2*pi*t*ff(4));

%% 
 figure

% pour l'affichage j'utilise la fonction plot pour tracer l'enveloppe du
% signal

plot(t,xk)
hold on
plot(t,xrec)
legend('Signal originel','Signal reconstitué')

%Error moyenne quadratique (MSE : Mean square error) :
error = sum(abs(xk-xrec).^2)./length(xk)

%% Signal inconnu : sig3_quidonc
% Analyse et interprétation
% Fs1 = Fs/4 avec (Fs = 8192 Hz)
% Après analyse de sig2_quidonc.mat, fmax = 1040 Hz
% Pour respecter le critère de Shannon il faut que Fs >= 2*1040 = 2080 Hz

% Or sig3_quidonc.mat a été échantillonné à une fréquence Fs1= Fs/4 =
% 8192/4 = 2048 Hz; Donc le critère de Shannon n'est pas respecté ==>
% repliement ou recouvrement de la fréquence 1040 : Fs-fmax = 2048-1040 =
% 1008 Hz.

% 4. Ce probl`eme n4aurait jamais dˆu intervenir exp´erimentalement. Pourquoi ?
% En utilisant un filtre analogique anti-repliement à la fréquence maximale
% càd 1040 Hz, le critère de Shannon sera respecté.
% Rôle du filtre anti-repliement : c'est pour éviter de "mal" choisir la
% fréquence d'échantillonnage grâce à sa fréquence de coupure.
