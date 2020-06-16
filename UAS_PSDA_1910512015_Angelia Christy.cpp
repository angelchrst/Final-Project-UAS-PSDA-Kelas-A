/*
Nama	: Angelia Christy
NIM		: 1910512015
E-mail	: angeliachrst@gmail.com
*/

# include <iostream>
# include <cstdlib>
using namespace std;

struct node
{
    int info;
    struct node *kiri;
    struct node *kanan;
} *root;

class BST
{
    public:
        void letak(int, node **, node **);    
        void insert(node *, node *);
        void preorder(node *);
        void inorder(node *);
        void postorder(node *);
        void hapus(int);
        void kasus_1(node *,node *);
        void kasus_2(node *,node *);
        void kasus_3(node *,node *);
        void terkecil(struct node *root);
        void terbesar(struct node *root);
        void reset(node *root);
        void cari(int);
        BST()
        {
            root = NULL;
        }
};

// menu utama
int main()
{
    int pilihan, angka, d;
    BST bst;
    node *temp;
    while (1)
    {
        cout<<"\n =========================="<<endl;
        cout<<" Operasi Binary Search Tree"<<endl;
        cout<<" =========================="<<endl;
        cout<<" 1. Masukkan elemen"<<endl;
        cout<<" 2. Tampilkan BST (Inorder, Preorder, Postorder)"<<endl;
        cout<<" 3. Hapus elemen "<<endl;
        cout<<" 4. Tampilkan nilai terbesar dan terkecil"<<endl;
        cout<<" 5. Reset BST"<<endl;
        cout<<" 6. Keluar program"<<endl;
        cout<<" Masukkan pilihan : ";
        cin>>pilihan;
        switch(pilihan)
        {
        case 1:
            temp = new node;
            cout<<" Masukkan angka yang ingin ditambahkan : ";
	    	cin>>temp->info;
            bst.insert(root, temp);
            break;
            
        case 2:
            cout<<"\n Preorder :"<<endl;
            bst.preorder(root);
            cout<<endl;
            
            cout<<" Inorder :"<<endl;
            bst.inorder(root);
            cout<<endl;
            
            cout<<" Postorder :"<<endl;
            bst.postorder(root);
            cout<<endl;
            break;
            
        case 3:
            if (root == NULL)
            {
                cout<<"\n Tree kosong, tidak ada yang bisa dihapus"<<endl;
                continue;
            }
            cout<<" Masukkan angka yang ingin dihapus : ";
            cin>>angka;
            bst.hapus(angka);
            cout<<"\n Elemen telah dihapus"<<endl;
            break;
            
        case 4:
        	bst.terkecil(root);
        	bst.terbesar(root);
        	break;
        	
		case 5:
			bst.reset(root);
			cout<<"\n BST telah di reset"<<endl;
			break;
		    
        case 6:
            exit(1);
        default:
            cout<<"\n Pilihan tidak tersedia"<<endl;
        }
    }
}
 
// letak elemen dalam Tree
void BST::letak(int elemen, node **sbr, node **lok)
{
    node *ptr, *ptrsimpan;
    if (root == NULL)
    {
        *lok = NULL;
        *sbr = NULL;
        return;
    }
    if (elemen == root->info)
    {
        *lok = root;
        *sbr = NULL;
        return;
    }
    if (elemen < root->info)
        ptr = root->kiri;
    else
        ptr = root->kanan;
    ptrsimpan = root;
    while (ptr != NULL)
    {
        if (elemen == ptr->info)
        {
            *lok = ptr;
            *sbr = ptrsimpan;
            return;
        }
        ptrsimpan = ptr;
        if (elemen < ptr->info)
            ptr = ptr->kiri;
	else
	    ptr = ptr->kanan;
    }
    *lok = NULL;
    *sbr = ptrsimpan;
}
 
// masukkan elemen dalam Tree
void BST::insert(node *tree, node *newnode)
{
    if (root == NULL)
    {
        root = new node;
        root->info = newnode->info;
        root->kiri = NULL;
        root->kanan = NULL;
        cout<<"\n Root node telah ditambahkan"<<endl;
        return;
    }
    if (tree->info == newnode->info)
    {
        cout<<"\n Elemen sudah ada dalam Tree"<<endl;
        return;
    }
    if (tree->info > newnode->info)
    {
        if (tree->kiri != NULL)
        {
            insert(tree->kiri, newnode);	
	}
	else
	{
            tree->kiri = newnode;
            (tree->kiri)->kiri = NULL;
            (tree->kiri)->kanan = NULL;
            cout<<"\n Node kiri ditambahkan"<<endl;
            return;
        }
    }
    else
    {
        if (tree->kanan != NULL)
        {
            insert(tree->kanan, newnode);
        }
        else
        {
            tree->kanan = newnode;
            (tree->kanan)->kiri = NULL;
            (tree->kanan)->kanan = NULL;
            cout<<"\n Node kanan ditambahkan"<<endl;
            return;
        }	
    }
}


// preorder
void BST::preorder(node *ptr)
{
    if (root == NULL)
    {
        cout<<" Tree kosong\n";
        return;
    }
    if (ptr != NULL)
    {
        cout<<"  "<<ptr->info;
        preorder(ptr->kiri);
        preorder(ptr->kanan);
    }
}

// inorder
void BST::inorder(node *ptr)
{
    if (root == NULL)
    {
        cout<<" Tree kosong\n";
        return;
    }
    if (ptr != NULL)
    {
        inorder(ptr->kiri);
        cout<<"  "<<ptr->info;
        inorder(ptr->kanan);
    }
}
  
// postorder
void BST::postorder(node *ptr)
{
    if (root == NULL)
    {
        cout<<" Tree kosong\n";
        return;
    }
    if (ptr != NULL)
    {
        postorder(ptr->kiri);
        postorder(ptr->kanan);
        cout<<"  "<<ptr->info;
    }
}
 
// menghapus elemen dari Tree
void BST::hapus(int elemen)
{
    node *sumber, *lokasi;
    if (root == NULL)
    {
        cout<<"\n Tree kosong"<<endl;
        return;
    }
    letak(elemen, &sumber, &lokasi);
    if (lokasi == NULL)
    {
        cout<<"\n Elemen tidak tersedia dalam Tree"<<endl;
        return;
    }
    if (lokasi->kiri == NULL && lokasi->kanan == NULL)
        kasus_1(sumber, lokasi);
    if (lokasi->kiri != NULL && lokasi->kanan == NULL)
        kasus_2(sumber, lokasi);
    if (lokasi->kiri == NULL && lokasi->kanan != NULL)
        kasus_2(sumber, lokasi);
    if (lokasi->kiri != NULL && lokasi->kanan != NULL)
        kasus_3(sumber, lokasi);
    free(lokasi);
}
 
// hapus elemen-kasus 1
void BST::kasus_1(node *sbr, node *lok )
{
    if (sbr == NULL)
    {
        root = NULL;
    }
    else
    {
        if (lok == sbr->kiri)
            sbr->kiri = NULL;
        else
            sbr->kanan = NULL;
    }
}
 
// hapus elemen-kasus 2
void BST::kasus_2(node *sbr, node *lok)
{
    node *child;
    if (lok->kiri != NULL)
        child = lok->kiri;
    else
        child = lok->kanan;
    if (sbr == NULL)
    {
        root = child;
    }
    else
    {
        if (lok == sbr->kiri)
            sbr->kiri = child;
        else
            sbr->kanan = child;
    }
}
 
// hapus elemen-kasus 3
void BST::kasus_3(node *sbr, node *lok)
{
    node *ptr, *ptrsimpan, *suc, *parsuc;
    ptrsimpan = lok;
    ptr = lok->kanan;
    while (ptr->kiri != NULL)
    {
        ptrsimpan = ptr;
        ptr = ptr->kiri;
    }
    suc = ptr;
    parsuc = ptrsimpan;
    if (suc->kiri == NULL && suc->kanan == NULL)
        kasus_1(parsuc, suc);
    else
        kasus_2(parsuc, suc);
    if (sbr == NULL)
    {
        root = suc;
    }
    else
    {
        if (lok == sbr->kiri)
            sbr->kiri = suc;
        else
            sbr->kanan = suc;
    }
    suc->kiri = lok->kiri;
    suc->kanan = lok->kanan;
}

// nilai terkecil
void BST::terkecil(struct node *root)
{
	if (root == NULL)
	{
		cout<<"\n Tree Kosong\n";
		return;
	}
	while(root != NULL && root->kiri != NULL)
	{
		root = root->kiri;
	}
	printf("\n Nilai terkecil adalah %d", root->info);
}

// nilai terbesar
void BST::terbesar(struct node *root)
{
	if (root == NULL)
	{
		cout<<" Tree Kosong\n";
		return;
	}
	while (root != NULL && root->kanan != NULL)
	{
		root = root->kanan;
	}
	printf("\n Nilai terbesar adalah %d \n", root->info);
}

// reset BST
void BST::reset(node *root)
{
	if (root != NULL)
	{
		reset(root->kiri);
		reset(root->kanan);
		delete(root);
		root == NULL;
	}
}
