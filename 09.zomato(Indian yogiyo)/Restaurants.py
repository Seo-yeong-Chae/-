# -*- coding: utf-8 -*-
"""FastCampus.ipynb

Automatically generated by Colaboratory.

이 파일은 코랩 환경에서 실행하도록 코드가 짜여져 있습니다 -> 'https://colab.research.google.com/'. 
그리고 상위 폴더에 있는 "restaurants.zip"을 압축 해제한 "restaurants.csv"가 구글 드라이브의 '내 드라이브' 폴더에 첨부되어야 합니다. 코드의 csv 파일 참조 경로가 '/content/drive/My Drive'이기 때문입니다.
"""

import math
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

plt.style.use('seaborn')

from google.colab import drive
drive.mount('/content/drive')

zmt = pd.read_csv('/content/drive//My Drive/zomato.csv', error_bad_lines=False)

zmt.info()

print("총 데이터 개수 : ", zmt.shape[0]*zmt.shape[1])
print("총 결측치 수 : {:.2f} = 전체 데이터의 {:.2f}%".format(zmt.isnull().sum().sum(), zmt.isnull().sum().sum()*100/(zmt.shape[0]*zmt.shape[1])))
print("전체 식당 수 : ", zmt['name'].nunique())

zmt = zmt.drop(['url', 'phone', 'menu_item'], axis = 1)

print('duplicated data count: ', zmt.duplicated().sum())

zmt.drop_duplicates(inplace=True)
zmt.info()

#컬럼 별 null 개수 확인하기
zmt.isnull().sum()

#nan 값이 있는 행을 삭제한 데이터 프레임 생성(not null_zmt) -> 리뷰를 토대로한 감정 분석할 때 사용할 예정 
nn_zmt = zmt.dropna(how = 'any')
nn_zmt.info()

print("nn_zmt's columns : \n\t",nn_zmt.columns,'\n',"zmt' columns : \n\t", zmt.columns)

nn_zmt = zmt.rename(columns={'approx_cost(for two people)':'cost', 'listed_in(type)':'type',
       'listed_in(city)':'city'})
zmt = zmt.rename(columns={'approx_cost(for two people)':'cost', 'listed_in(type)':'type',
       'listed_in(city)':'city'})
print("nn_zmt's columns : \n\t",nn_zmt.columns,'\n',"zmt' columns : \n\t", zmt.columns)

print(zmt['cost'].unique())
print(zmt.info())

#cost 칼럼의 데이터 타입을 object에서 string으로 변경해서 콤마(,) 삭제 후 다시 float으로 변경
zmt['cost'] = zmt['cost'].astype(str)
zmt['cost'] = zmt['cost'].replace(',', '_', regex = True)
zmt['cost'] = zmt['cost'].astype(float)
print(zmt['cost'].unique())

print(zmt['rate'].unique())

#rate 칼럼의 데이터 타입을 string으로 변환해서 '/5' 제거 후 float으로 변경
zmt['rate'] = zmt['rate'].astype(str)
zmt['rate'] = zmt['rate'].replace('/5', '', regex=True)
zmt['rate'] = zmt['rate'].replace('NEW', np.nan, regex=True)
zmt['rate'] = zmt['rate'].replace('-', np.nan, regex=True)

zmt.reset_index(drop=True) 
zmt['rate'] = zmt['rate'].astype(float)

zmt.head(3)

zmt['online_order'] = zmt['online_order'].map({"Yes":1, "No":0})
zmt['book_table'] = zmt['book_table'].map({"Yes":1, "No":0})
zmt.head(3)

zmt.info()

#매장 수가 가장 많은 레스토랑은?
f, ax = plt.subplots(1, 1, figsize=(12, 6))
sns.barplot(x= zmt['name'].value_counts()[:10], y=zmt['name'].value_counts()[:10].index, palette='mako')
plt.title('Top 10 restaurants having franchises in bangalore', size=18)
plt.xlabel('Franchise count')
plt.ylabel('Restaurant name')

plt.figure(figsize=(12, 6))

sns.barplot(x = zmt['type'].value_counts()[:15], y = zmt['type'].value_counts()[:15].index, palette='icefire')
plt.title('Management type of retaurant')
plt.xlabel('Number of stores')
plt.ylabel('Type of restaurant')

f2, ax2 = plt.subplots(1, 1, figsize=(12, 12))

g = sns.countplot(zmt['city'], ax=ax2)
g.set_xticklabels(g.get_xticklabels(), rotation=45, ha='right')
plt.title('Number of restaurants in bangalore per district', size=18)
plt.ylabel('')

f3, ax3 = plt.subplots(1, 2, figsize=(13, 5))

sns.countplot(zmt['online_order'], palette='dark:salmon_r', ax=ax3[0])
ax3[0].set_title('Number of restaurants available on online')
ax3[0].set_xlabel('Whether available on online')

sns.countplot(zmt['book_table'], palette='YlOrBr', ax=ax3[1])
ax3[1].set_title('Number of restaurants available for booking tables')
ax3[1].set_xlabel('Whether available for booking tables')

f4, ax4 = plt.subplots(1, 2, figsize = (16, 7))

sns.boxplot(x = zmt['online_order'], y = zmt['cost'], palette = 'dark:salmon_r', ax = ax4[0])
ax4[0].set_title('Restaurants available on online', size=18)
ax4[0].set_ylabel('average food expenses(for 2 people)', fontsize=14)
ax4[0].set_xlabel('Whether available on online', fontsize=14)
ax4[0].set_ylim(0, 3000) #outlier 제거

sns.boxplot(x = zmt['book_table'], y = zmt['cost'], palette = 'YlOrBr', ax = ax4[1])
ax4[1].set_title('Restaurants available for booking tables', size = 18)
ax4[1].set_ylabel('')
ax4[1].set_xlabel('Whether available for booking tables', fontsize=14)
ax4[1].set_ylim(0, 3000)

f5,ax5 = plt.subplots(1, 2, figsize = (16, 7))

sns.boxplot(x = zmt['online_order'], y = zmt['rate'], palette = 'dark:salmon_r', ax = ax5[0])
ax5[0].set_title('Rate depending on whether available on online', size=18)
ax5[0].set_ylabel('average rate', fontsize=14)
ax5[0].set_xlabel('Whether available on online', fontsize=14)

sns.boxplot(x = zmt['book_table'], y = zmt['rate'], palette = 'YlOrBr', ax = ax5[1])
ax5[1].set_title('Rate depending on whether available for booking tables', size = 18)
ax5[1].set_ylabel('')
ax5[1].set_xlabel('Whether available for booking tables', fontsize=14)

oo_per_rate = pd.crosstab(zmt['rate'], zmt['online_order'])
bt_per_rate = pd.crosstab(zmt['rate'], zmt['book_table'])

f6, ax6 = plt.subplots(1, 2, figsize = (25, 11))

sns.set_style('white')

oo_rate_plot = oo_per_rate.plot(kind = 'bar', stacked=False, ax = ax6[0])
ax6[0].set_title('Restaurants number per rate and whether available on online', size=18)
plt.xlabel('')
plt.ylabel('')
oo_rate_plot.set_xticklabels(oo_rate_plot.get_xticklabels(), rotation = 0)

bt_rate_plot = bt_per_rate.plot(kind = 'bar', stacked=False, ax = ax6[1])
ax6[1].set_title('Restaurants number per rate and whether available for book_table', size = 18)
plt.xlabel('')
plt.ylabel('')
bt_rate_plot.set_xticklabels(bt_rate_plot.get_xticklabels(), rotation = 0)

#텍스트 클라우드 패키지 삽입
from wordcloud import WordCloud, STOPWORDS

zmt['rest_type'].unique()

top_type_idx = zmt['rest_type'].value_counts()[:3].index 
#index <- ['Quick Bites', 'Casual Dining', 'Cafe']

#레스토랑 타입별로 워드클라우드 그리는 함수 만들기

def zomato_wordcloud(top_type_idx):
  plt.figure(figsize = (20, 20))
  for idx, rest_type in enumerate(top_type_idx):
    plt.subplot(1, 3, idx+1)
    dishes=""
    data = zmt[zmt['rest_type'] == rest_type]
    
    #dish_liked에 있는 단어들을 쪼개준다
    for dish_object in data['dish_liked']:
      dish_list = str(dish_object).split(", ")
      #if문에서 np.NaN값 필터링
      if len(dish_list) < 2 :
        continue
      dishes =dishes+ " ".join(dish_list)+" "
    wordcloud = WordCloud(background_color='white', colormap='seismic', collocations=False, stopwords=stopwords, width=1200, height=1200).generate(dishes)
    plt.imshow(wordcloud)
    plt.title(type)
    plt.axis("off")

stopwords = set(STOPWORDS)
zomato_wordcloud(top_type_idx)
