%% Algorytmy genetyczne, lab.1, Tomasz K¹kol
clear; close all; clc;

%config figure design
figure('units','normalized','outerposition',[0 0 1 1])
set(gcf,'color','w');

%variables
V = 10000;
generations = 30;

% data for ex.3.A
alele_A = floor(V/3);
alele_B = floor(V/3);
alele_C = floor(V/3);

%{
% data for ex.3.B
alele_A = floor(V/1);
alele_B = 0;
alele_C = 0;

% data for ex.3.C
alele_A = 0;
alele_B = floor(V/1);
alele_C = 0;
%}

genes = alele_A + alele_B + alele_C;
A = zeros(1, generations);
B = zeros(1, generations);
C = zeros(1, generations);

%% ex.3.1
% solution
figure(1)
for generation = 1:generations 
    A(1, generation) = alele_A;
    B(1, generation) = alele_B;
    C(1, generation) = alele_C;
    a=0;
    b=0;
    c=0;
    
    for alel_A = 1 : alele_A
        if(rand(1) > 0.5)
            a = a + 1;
        else
            b = b + 1;
        end    
    end
    
    for alel_B = 1 : alele_B
        x = rand(1);
        if(x < 0.3333)
            c = c + 1;
        elseif(x < 0.6666)
            b = b + 1;
        else
            a = a + 1;
        end    
    end
    
    for alel_C = 1 : alele_C
        if(rand(1) > 0.5)
            c = c + 1;
        else
            b = b + 1;
        end    
    end
	alele_A = a;
    alele_B = b;
    alele_C = c;
end

hold on
line(1:generations, A/genes ,  'LineWidth', 2, 'Color', 'g');
hold on
line(1:generations, B/genes , 'LineWidth', 2, 'Color', 'b');
hold on
line(1:generations, C/genes , 'LineWidth', 2, 'Color', 'k');
axis([0, generations, 0, 1]);
xlabel('Numer pokolenia', 'fontsize', 14);
ylabel('Udzia³ genu z danym alelem w populacji ', 'fontsize', 14);
title('Charakterystyka zmiany udzia³u genów z poszczególnymi alelami w kolejnych pokoleniach.', 'fontsize', 14);
legend('Gen A',...
              'Gen B',...
              'Gen C');
grid on;
hold off
   
%% ex.3.2
%{
% remember to comment (hide) example 3.1 or redefine previously modified variables
% solution 2
figure(1)
for generation = 1:generations 
    A(1, generation) = alele_A;
    B(1, generation) = alele_B;
    C(1, generation) = alele_C;
    a=0;
    b=0;
    c=0;
    for alel_A = 1 : alele_A
       x = rand(1);
       if(x < 0.3333)
            a = a + 1;
        elseif(x < 0.6666)
            b = b + 1;
        end    
    end
    
    for alel_B = 1 : alele_B
        x = rand(1);
        if(x < 0.3333)
            a = a + 1;
        elseif(x < 0.6666)
            b = b + 1;
        else
            c = c + 1;
        end    
    end
    
    for alel_C = 1 : alele_C
       x = rand(1);
       if(x < 0.3333)
            c = c + 1;
         elseif(x < 0.6666)
            b = b + 1;
        end    
    end
	alele_A = a;
    alele_B = b;
    alele_C = c;
end

hold on
line(1:generations, A/genes ,  'LineWidth', 2, 'Color', 'g');
hold on
line(1:generations, B/genes , 'LineWidth', 2, 'Color', 'b');
hold on
line(1:generations, C/genes , 'LineWidth', 2, 'Color', 'k');
axis([0, generations, 0, 1]);
xlabel('Numer pokolenia', 'fontsize', 14);
ylabel('Udzia³ genu z danym alelem w populacji ', 'fontsize', 14);
title('Charakterystyka zmiany udzia³u genów z poszczególnymi alelami w kolejnych pokoleniach.', 'fontsize', 14);
legend('Gen A',...
              'Gen B',...
              'Gen C');
grid on;
hold off
%}