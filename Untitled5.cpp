#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>


using namespace std;

// Yazarlara ait düðümün bilgileri struct olarak tanýmlandý
struct node
{	
    int ID; // yazara ait ID bilgisi
    int kitap_sayisi;
    string yazar;
    struct node *next; // yazarlar arasý geçiþ için next,prev pointerlarý kullanýlýr 
    struct node *prev;
}*start;

// Kitaplara ait düðümün bilgileri struct larak tanýmlandý
struct kitap
{
	int ID; //kitaplara ait ID bilgisi
    int parentID; // Kitabýn yazarýna ait ID bilgisi
    string kitap_adi;
    string kitap_turu;
    int sayfa;
    int stok;
	string paragraf;
	  
    struct kitap *next; // kitaplar arasý geçiþ için next,prev pointerý kullanýlýr
    struct kitap *prev;
}*start_k;

//  Kitap listesi için class tanýmlandý, gerekli fonksiyonlar kullanýldý
 class kitap_list
{
    public:
        void create_kitap_list(int ID,int parentID,string kitap_adi,string kitap_turu,int sayfa,int stok);
        void delete_kitap_element(int ID);
        void search_kitap_element(int ID,string yazar);
        void display_kitap_dlist();
        void count_kitap();
        // yapýcı fonksiyonu
		kitap_list()
        {
            start_k = NULL;  
        }
};

//  Yazar listesi için class tanýmlandý, gerekli fonksiyonlar kullanýldý
class double_llist
{
    public:
        void create_list(int ID,string yazar,int kitap_sayisi);
        void delete_element(int ID);
        void search_element(int ID,string yazar);
        void display_dlist();
        void count();
        // yapýcý fonksiyonu
		double_llist()
        {
            start = NULL;  
        }
};

// Yazar sayýsý toplamý, yazarlarý yazdýrýrken kullanýlmasý için tanýmlandý
int getTotalAuthor(){
	ifstream fe("yazar.dat"); // fe tanýmý yazar.dat dosyasýna okuma yapmaktdýr
	int i = 0;
	string line;
	while (getline(fe,line)){ // Burada Kaç satýr var bunu buluyoruz
		++i;
	}
	return i;
}

// integer ý stringe ceviriyoruz
// writeTo fonksiyonlarý için kullanýldý
string myitos (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

// myfile degiskeni tanýmlanarak yazar.dat dosyasýndan okuma yapýlýyor.  
void readTo(double_llist name)
    {
    	string yazar;
    	int ID,kitap_sayisi;
    	string y;
    	string I,k;
    	ifstream myfile ("yazar.dat");
    	if (!myfile)
    	{
    		cout<<"yazar.dat not found on program directory";
    		exit(1);
    		
		}
		else{	
			for(int i=0; i<getTotalAuthor();i++){
    		getline(myfile,I,'='); // dosyada kullanýldýgý icin implementer olarak geciyor
			ID = atoi(I.c_str());  // stringi integer a ceviriyor..
    		getline(myfile,y,'=');
    		getline(myfile,k,'=');
    		kitap_sayisi = atoi(k.c_str());
    		name.create_list(ID,y,kitap_sayisi);
			}	
		}
    	
		
    }
    
// Yeni yazar oluþturunca dosyaya aktarma iþini yapýyor    
void writeTo(int ID,string yazar,int kitap_sayisi){
	fstream fs;
	string a="\n";
	a +=  myitos(ID);
	a += "=";
	a += yazar;
	a += "=";
	a += myitos(kitap_sayisi);
	a += "=";
  //fstream::app dosyaya ekleme için kullanýldý	
  fs.open ("yazar.dat", std::fstream::in | std::fstream::out | std::fstream::app);
  fs << a;
  fs.close();
}

// Kitap sayýsý bulunuyor
int getTotalKitap(){
	ifstream fe("kitap.dat"); // kitap.dat dosyasýndan sayý hesaplandý.
	int i = 0;
	string line;
	while (getline(fe,line)){
		++i;
	}
	return i;
}

// Kitap bilgileri Programa aktarýlýyor
void readToKitap(kitap_list name)
    {
    	string kitap_adi;
    	string kitap_turu;
    	int ID,parentID,sayfa,stok;
    	string I,p,s,st;
    	
    	ifstream myfile ("kitap.dat");
    	if (!myfile) // dosya yoksa uyarý verir
    	{
    		cout<<"kitap.dat not found on program directory";
    		exit(1);
    		
		}
		else{	
			for(int i=0; i<getTotalKitap();i++){
    		getline(myfile,I,'=');
			ID = atoi(I.c_str());
			// ID degiskeni dosyadan okunuyor
			getline(myfile,p,'=');
			parentID = atoi(p.c_str());
			
    		getline(myfile,kitap_adi,'=');
    		
    		getline(myfile,kitap_turu,'=');
    		
    		getline(myfile,s,'=');
			sayfa = atoi(s.c_str());
			
			getline(myfile,st,'=');
			stok = atoi(st.c_str());
    		// Burada yeni kitap olusturuluyor
    		name.create_kitap_list(ID,parentID,kitap_adi,kitap_turu,sayfa,stok);
			}
		}
    	
		
    }
// Kitaplarý kitap.dat dosyasýna yazýyor    
void writeToKitap(int ID,int parentID,string kitap_adi,string kitap_turu,int sayfa,int stok){
	fstream fs;
	string a="\n";
	a +=  myitos(ID);
	a += "=";
	a += myitos(parentID);
	a += "=";
	a += kitap_adi;
	a += "=";
	a += kitap_turu;
	a += "=";
	a += myitos(sayfa);
	a += "=";
	a += myitos(stok);
	a += "=";
	
  fs.open ("kitap.dat", std::fstream::in | std::fstream::out | std::fstream::app);
  fs << a;
  fs.close();
}





// Ana menüyü access degiskeni ile cagýrýyor
// access admin mi kullanýcý mý bunu belirtiyor.
//1-> user 2->admin 
int callMainMenu(int access){
	
	int choice, ID, kitap_sayisi,i=1;
    string yazar;
    double_llist dl; // yazar listesi
    kitap_list kl;   //kitap listesi
    bool list=false; 
	readTo(dl); //program acýlýnca otomatik olarak yazarlarý içe aktarýr
	readToKitap(kl);
	string user;
	//Burada yetki kýsmý belirleniyor
	if(access==2){
		user="Administration";
	}
	else if(access==1){
		user="User";
	}
  
    while (1)
    {x:
	system("color 4f"); // arayüz için renk eklendi
    	
      if (list==false){ // listenin görüntülenmesi kontrol edildi
        cout<<endl<<"----------------------------"<<endl;
        cout<<endl<<"Library "<<user<<" Panel"<<endl;
        cout<<endl<<"----------------------------"<<endl;    
		// admin ise tüm secenekler gösteriliyor  
        if(access==2){
        	
		cout<<"1.Edit Books of Author"<<endl;
		cout<<"2.Add Author"<<endl; 
        cout<<"3.Delete Author"<<endl; 
        cout<<"4.Display Authors"<<endl;
        cout<<"5.Count of Authors"<<endl;    	
		cout<<"6.Quit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch ( choice )
        {
        case 1:
        	system("cls");
        // menü yazdýrýldý 1 ile her ihtimalde while e girdik	
         while (1){
		 	//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    		int choice;
    		int kID, ksayfa,kstok,parentID;
        	string k_adi,k_turu;
        	bool list=false;
        	
        	cout<<endl<<"----------------------------"<<endl;
        	cout<<endl<<"Library Administration Panel"<<endl;
        	cout<<endl<<"----------------------------"<<endl;    
			//Kitap düzenleme menüsü     
        	cout<<"0.Add Book"<<endl;
			cout<<"1.Delete Book"<<endl; 
        	cout<<"2.Search Book by Name"<<endl;
        	cout<<"3.Search Book by Containing Words"<<endl;
        	cout<<"4.Count of All Books"<<endl;
        	cout<<"5.Display Books"<<endl;
        	cout<<"6.Go Back"<<endl;
        	
        	cout<<"Enter your choice : ";
        	cin>>choice;
			switch ( choice ){
        	case 0:	
    	        cout<<"Enter ID for Book ";
				cin>>kID;
				cout<<"Enter This Book's Author's ID ";
			  	cin>>parentID;
			  	cout<<"Enter Book Name ";
			  	getline(cin>>ws,k_adi);
			    cout<<"Enter Book Type ";
			    getline(cin>>ws,k_turu);
			  	cout<<"Enter Page Amount ";
			  	cin>>ksayfa;
			  	cout<<"Enter This Book's Amount ";
			  	cin>>kstok;
			  
			  kl.create_kitap_list(kID,parentID,k_adi,k_turu,ksayfa,kstok);
			  writeToKitap(ID,parentID,k_adi,k_turu,ksayfa,kstok);
				break;
			case 1:
				 if (start_k == NULL)
            	{                      
                	cout<<"Book list empty,nothing to delete"<<endl;   
                	break;
            	}
            	cout<<"Enter the ID for delete a Book: ";
            	int idid;
            	cin>>idid;
            	system("cls");
            	kl.delete_kitap_element(idid);
            	
            	cout<<endl;
            	break;
			case 5:
				system("cls");
        		list=true;
            	kl.display_kitap_dlist();
        	    int quit;
            	cin>>quit;
				switch(quit){
				case 1:
					list=false;
					break;
					system("cls");
            	default:
            		list=false;
            		system("cls");
            		break;
					}
           		cout<<endl;
           		break;
			case 6:
				system("cls");
				goto x;
				break;
			default://Aaaaaaaaaaaaaaaaaaaaaaaaaaaaa
				system("cls");
				cout<<"Wrong Choice";
				
				}
				system("cls");
				}
            
            
        case 2:
            cout<<"Enter ID for Author ";
            cin>>ID;
            cout<<"Enter Name for Author ";
            cin>>yazar;
            cout<<"Count of books ";
            cin>>kitap_sayisi;
            dl.create_list(ID,yazar,kitap_sayisi);
            writeTo(ID,yazar,kitap_sayisi);
            cout<<"------------------\n";
            for(int o=0;o<kitap_sayisi;o++)
            { int kID, ksayfa,kstok;
              string k_adi,k_turu;
              cout<<"Enter ID for Book ";
			  cin>>kID;
			  cout<<"Enter Book Name ";
			  getline(cin>>ws,k_adi);
			  cout<<"Enter Book Type ";
			  getline(cin>>ws,k_turu);
			  cout<<"Enter Page Amount ";
			  cin>>ksayfa;
			  cout<<"Enter This Book's Amount ";
			  cin>>kstok;
			  //yeni kitap olusunca dosyaya atýyor
			  writeToKitap(kID,ID,k_adi,k_turu,ksayfa,kstok);
			  kl.create_kitap_list(kID,ID,k_adi,k_turu,ksayfa,kstok);
			}
            system("cls");
            cout<<"Author and books created";
            break;
        case 3:
            if (start == NULL)
            {                      
                cout<<"List empty,nothing to delete"<<endl;   
                break;
            }
            cout<<"Enter the ID for delete an author: ";
            cin>>ID;
            system("cls");
            dl.delete_element(ID);//ID bilgisi kitap silmede kullanýldý
            break;
        case 4:
        	system("cls");
        	list=true;
            dl.display_dlist();
            int quit;
            cin>>quit;
			switch(quit){
				case 1:
					list=false;
					system("cls");
					break;
					
            	default:
            		list=false;
            		system("cls");
            		break;
			}
			
            cout<<endl;
            break;
        case 5:
        	system("cls");
            dl.count(); // yazar listesindeki yazar sayýsý
            break;    
        case 6:
            exit(1);
        default:
        	system("cls");
            cout<<"Wrong choice";
        }
      
        
    }
	//Kullanýcý Menüsü
	else if(access==1){
    	cout<<"1.Display Authors"<<endl;
        cout<<"2.Count of Authors"<<endl; 
		cout<<"3.Display Books"<<endl; 	
		cout<<"4.Count of Books"<<endl;
		cout<<"5.Quit"<<endl;
		int a;
		cout<<"Enter your choice : ";
    	cin>>a;
    	switch(a){
    		case 1:
        		system("cls");
        		list=true;
            	dl.display_dlist();//yazarlarý gösterir
            	int quit;
            	cin>>quit;
				switch(quit){
					case 1:
						list=false;
						break;
						system("cls");
            		default:
            			list=false;
            			system("cls");
            			break;
				}
			
            cout<<endl;
            break;
        case 2:
            dl.count();
            break;    
        case 3:
            kl.display_kitap_dlist(); // kitap listesini gösterir
            break; 
        case 4:                       // kitap sayýsý
            kl.count_kitap();
            break; 
        case 5:
            exit(1);
        default:
            cout<<"Wrong choice"<<endl; // yanlýþ seçimde 
		}
	}
      } 
    }
    return 0;
}

 // kitap_list classýna ait fonksiyon tanýmlandý	
 void kitap_list::create_kitap_list(int ID,int parentID,string kitap_adi,string kitap_turu,int sayfa,int stok)
{
    struct kitap *s2, *temp2;
    temp2 = new(struct kitap); 
    temp2->ID=ID;
    temp2->parentID=parentID;
    temp2->kitap_adi=kitap_adi;
    temp2->kitap_turu=kitap_turu;
    temp2->sayfa=sayfa;
    temp2->stok=stok;
    temp2->next = NULL;
    if (start_k == NULL)
    {
        temp2->prev = NULL; //
        start_k = temp2;
    }
    else
    {
        s2 = start_k;
        while (s2->next != NULL)
            s2 = s2->next;
        s2->next = temp2;
        temp2->prev = s2;
    }
}

// yazar classýna ait fonksiyon tanýmý yapýldý
void double_llist::create_list(int ID,string yazar,int kitap_sayisi)
{   //s baslangýc node unu belirler temp geçiþ yapar
    struct node *s, *temp;
    temp = new(struct node); 
    temp->ID = ID;
    temp->yazar=yazar;
    temp->kitap_sayisi=kitap_sayisi;
    temp->next = NULL;
    if (start == NULL)
    {
        temp->prev = NULL;
        start = temp;
    }
    else
    {
        s = start;
        while (s->next != NULL)
            s = s->next;
        s->next = temp;
        temp->prev = s;
    }
}
// yazar classýna ait silme fonksiyonu tanýmý
void double_llist::delete_element(int ID)
{
    struct node *tmp, *q;
     //Girilen ID, ilk yazarsa silinniyor
    if (start->ID == ID)
    {
        tmp = start;
        start = start->next;  
        start->prev = NULL;
        cout<<"Author Deleted";
        free(tmp);
        return;
    }
    q = start;
    //Silinmek istenen yazar ortadaysa
    while (q->next->next != NULL)
    {   
        if (q->next->ID == ID)  
        {
            tmp = q->next;
            q->next = tmp->next;
            tmp->next->prev = q;
            cout<<"Author Deleted";
            free(tmp);
            return;
        }
        q = q->next;
    }
    //Silinmek istenen yazar en sonda ise
    if (q->next->ID == ID)    
    { 	
        tmp = q->next;
        free(tmp);
        q->next = NULL;
        cout<<"Author Deleted";
        return;
    }
    
    cout<<"Author with ID= "<<ID<<" not found"<<endl;
}
// kitap classýna ait kitap silme fonksiyonu 
void kitap_list::delete_kitap_element(int ID)
{
    struct kitap *tmp2, *q2;
     //Girilen ID ilk kitapsa, siliniyor
    if (start_k->ID == ID)
    {
        tmp2 = start_k;
        start_k = start_k->next;  
        start_k->prev = NULL;
        cout<<"Book Deleted";
        free(tmp2);
        return;
    }
    q2 = start_k;
    //Girilen ID listenin ortasýndaysa
    while (q2->next->next != NULL)
    {   
        if (q2->next->ID == ID)  
        {
            tmp2 = q2->next;
            q2->next = tmp2->next;
            tmp2->next->prev = q2;
            cout<<"Book Deleted";
            free(tmp2);
            return;
        }
        q2 = q2->next;
    }
    //Girilen ID Liste sonundaysa
    if (q2->next->ID == ID)    
    { 	
        tmp2 = q2->next;
        free(tmp2);
        q2->next = NULL;
        cout<<"Book Deleted";
        return;
    }
    //Silinmek istenen Kitap listede yoksa uyarý verir
    cout<<"Book with ID= "<<ID<<" not found"<<endl;
}
 //kitap classýna ait kitap listeleme fonksiyonu tanýmlandý   
void kitap_list::display_kitap_dlist()
{   //liste boþsa
    struct kitap *q2;
    if (start_k == NULL)
    {
        cout<<"List empty,nothing to display"<<endl;
        return;
    }
    q2 = start_k;
    cout<<"List of Books :"<<endl;
    while (q2 != NULL)
    {
    	cout<<"-------\n";
        cout<<"ID: "<<q2->ID<<"\nKitap Adi: "<<q2->kitap_adi<<"\nKitap Turu: "<<q2->kitap_turu<<"\nKitap Sayfasi: "<<q2->sayfa<<"\nStok: "<<q2->stok<<endl;
        cout<<"-------\n";
        q2 = q2->next;
    }
    cout<<endl;
    cout<<"(1) Go Back"<<endl;
}

//Yazar classýna ait yazar listesini gösteren fonksiyon tanýmlandý
void double_llist::display_dlist()
{
    struct node *q;
    if (start == NULL)
    {
        cout<<"List empty,nothing to display"<<endl;
        return ;
    }
    q = start;
    cout<<"List of Authors :"<<endl;
    while (q != NULL)
    {
    	cout<<"-------\n";
        cout<<"ID: "<<q->ID <<"\nYazar: "<<q->yazar<<"\nKitap Sayisi: "<<q->kitap_sayisi<<endl;
        cout<<"-------\n";
        q = q->next;
    }
	cout<<endl;
    cout<<"(1) Go Back"<<endl;
}

//Yazar classýna ait yazarlarý sayan fonksiyon tanýmlandý
void double_llist::count()
{ 	
    struct node *q = start;
    int cnt = 0;
    while (q != NULL)
    {
        q = q->next;
        cnt++;
    }
    cout<<"Number of Authors are: "<<cnt<<endl;
}
//Kitap classýna ait kitaplarý sayan fonksiyon tanýmlandý
void kitap_list::count_kitap()
{ 	
    struct kitap *q = start_k;
    int cnt = 0;
    while (q != NULL)
    {
        q = q->next;
        cnt++;
    }
    cout<<"Number of Books are: "<<cnt<<endl;
}
//Giriþ ekraný baþlangýcý
//Toplam user sayýsý bulunuyor
//For döngüsü için kullanýldý
int getTotalUser(){
	ifstream fe("user.dat");
	int i = 0;
	string line;
	while (getline(fe,line)){
		++i;
	}
	return i;
}
//Kullanýcý adý ve þifresi Dosyada var mý kontrol ediliyor
int userControl(string username , string password){
	string userData;
  	string passData;
  	string accessData;
  	string line;
  	ifstream myfile ("user.dat");
  	if (!myfile)
  		cout << "Failed to open user data file\n";
  	bool admin;
  	int match=0;
  	for (int i=0;i<getTotalUser();i++){
  		getline (myfile,userData,'=');
    	getline (myfile,passData,'=');
    	getline (myfile,accessData,'=');
    	getline (myfile,line,'=');//\n newline operatorunu temizliyor
   		if(username==userData && password==passData){
   			if(accessData=="admin")
   				{admin=true;}
   				++match; //eþleþince 
		   }
	}
		if(admin==true && match==1)
			return 2;//admin giriþi 
		else if(admin==false && match==1){
			return 1;//user giriþi
		}
		else 
			return 0;//eþleþme bulunamadý
}

/*Yanlýþ giriþ limiti aþýlýnca belirlenen
 süre kadar giriþ yapýlamýyor,sonrasýnda giriþ
 ekraný yeniden görüntüleniyor
*/
int timer(int sec){
	int i=sec; //sec degeri aþaðýdaki fonksiyonda belirlenerek kullanýlýyor
	for(int s=0;s<=sec*160;s++){
		system("cls");
		cout<<"\t\t\t\tWait ";
		cout<<i<<" seconds for login";
		if(s%160==0) //16gb ram i7 iþlemcide ortalama tahminen 1sn sürüyor
		i--;	 
			
		
	}
}

// Giriþ ekraný görüntüleme
int colorizedLogin(){
	a:
	system("cls");
	int i=1;
	system("color 4f");
	system("title My Lil' Library v1.0");
	cout << "\t\t\t\t Library Login Panel \n";
	x:
	string username,pass;
	cout<<"\t\t\t\t  .______________.\n\t\t\t\t  |  Username :  |\n\t\t\t\t  |______________|\n\t\t\t\t\t";
	cin>>username;
	cout<<"\t\t\t\t  .______________.\n\t\t\t\t  |  Password :  |\n\t\t\t\t  |______________|\n\t\t\t\t\t";
	cin>>pass;
	int login=userControl(username,pass);
	if (login==2){
		cout << "Admin login succeed...";
		system("cls");
		callMainMenu(2);		
	}else if(login==1){
		cout << "User login succeed...";
		system("cls");
		callMainMenu(1);
	}else if(login==0){
		system("color 4f");
		system("cls");
		cout << "Login failed...\n";
		if(i<3){
			cout <<"("<< i<<"/3) failed login.\n";
			i++;
			
			goto x;
		}else{
		timer(10); //Giriþin engellenme süresi ayarlanýyor
		goto a;
		}
		
	}
}
//Giriþ ekraný sonu

int main()
{
    colorizedLogin();
    return 0;
}


