# -*- coding: utf-8 -*-


from PIL import Image 
import colorsys
import scipy
import glob
import numpy as np
from scipy import interpolate
from scipy import signal
import math
from math import floor
import matplotlib.pyplot as plt

    
def movingaverage(interval, window_size):
    window = np.ones(int(window_size))/float(window_size)
    return np.convolve(interval, window, 'same')


# Função que retorna o valor médio HSV de cada frame do vídeo
def analyze( imgFile ):
 
    img = Image.open(imgFile)
    width, height = img.size
        
    data = []    
    pixels = img.load()
    for x in range(width):
        for y in range(height):
            cpixel = pixels[x, y]
            data.append(cpixel)
            
    r=0
    g=0
    b=0
    counter=0
      
    for x in range(len(data)):
        r+=data[x][0]
        g+=data[x][1]
        b+=data[x][2]
        counter+=1;
    rAvg = r/counter
    gAvg = g/counter
    bAvg = b/counter
    return colorsys.rgb_to_hsv(rAvg, gAvg, bAvg)
   
# Itera a função de analise para os arquivos de imagem que representam cada frame do vídeo    

values = []

for Imagefile in glob.glob('Fotos/*[0-999].*'):
        values.append(analyze(Imagefile))
                
# Pega apenas os valores H do vetor de valores HSV dos frames

valuesh = []
for i in range (len(values)):
        valuesh.insert(i,values[i][2])

        
# Filtragem do sinal    
    
FreqMin = float(40)/60/50
FreqMax = float(230)/60/50

b,a =scipy.signal.butter(3,[FreqMin,FreqMax],'bandpass')  # Filtro ButterWorth
valuesFilter = scipy.signal.lfilter(b, a, valuesh, axis=-1, zi=None)

valuesFilter = movingaverage(valuesFilter,5)

# Deleta-se o primeiro 1,5 segundo para remover o offset do filtro

for i in range (45):
    valuesFilter = np.delete(valuesFilter,0,0)

# Interpolação do sinal, para passar de 30 Hz para 180 Hz

x = np.arange(0,6*len(valuesFilter),6)
tck = interpolate.splrep(x, valuesFilter, s=0)
xnew = np.arange(0,(6*len(valuesFilter))+1,1)
valuesInterp = interpolate.splev(xnew, tck, der=3)

   
# Detecção de picos   
# Mudar os valores do segundo parametro da função, que é o intervalo do tamanho dos picos que queremos achar
# Assim, temos que tentar achar os valores que retornam picos mais precisos
    
peakidx = scipy.signal.find_peaks_cwt(valuesInterp,np.arange(2,15)) 

lista = []

for i in range(len(peakidx)):
    if valuesInterp[peakidx[i]] >=0:
        lista.append([peakidx[i],valuesInterp[peakidx[i]]]) 

#lista[i][0]   			// tempo 
#lista[i][1]   			// valor H

janela = 1100	 #tamanho da janela em segundos
#lista = []     		# lista recebida
final = []     			# lista final
janela_at = janela
i = 0

def get_value(item):
	return item[1]

while lista[len(lista)-1][0] >= janela_at-janela:
    count = 0
    median = 0
    temp_lista = []
	
    while i<len(lista) and (lista[i][0] >= janela_at - janela) and (lista[i][0] < janela_at):
         temp_lista.append(lista[i])
         i += 1
    temp_sorted = sorted(temp_lista, key=get_value)
    if len(temp_sorted)%2 == 0:
        median = (temp_sorted[(len(temp_sorted)-1)/2][1] + temp_sorted[len(temp_sorted)/2][1])/2
    else:
        median = temp_sorted[int(len(temp_sorted)/2)][1]
	        
    #criterios de selecao dos peaks
    for j in range(0, len(temp_lista)):
        if temp_lista[j][1] < 0.8*median or temp_lista[j][1] > 1.2*median:
            count += 1
	       
    if count < 0.5*(len(temp_lista)):
        if (len(temp_lista) - count) >= 4:
             for j in range(0, len(temp_lista)):
                 if temp_lista[j][1] >= 0.8*median and temp_lista[j][1] <= 1.2*median:
                      final.append(temp_lista[j])
                        
	
    janela_at = janela_at + janela


def get_tempo(item):
	return item[0]
final = sorted(final, key=get_tempo) 

diff = []
for i in range (1,len(final)):
    diff.append(final[i][0]-final[i-1][0])


mediaDiff = 0

for i in range (len(diff)):
    mediaDiff += diff[i]
mediaDiff = mediaDiff/len(diff)

periodo = float(mediaDiff)/180
bpm = ((1/periodo)*60)
print bpm

