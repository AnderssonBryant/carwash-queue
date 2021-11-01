// Bryant Andersson (2301854706)
// LC01
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//struct data mobil
struct data_mobil{ 
	char plat_nomor[8];
	int jenis_mobil;
	int layanan[3];
	char waktu_pengerjaan;
	int cost;
};

// struct jalur 
struct jalur{
	struct data_mobil *dtm; // memasukkan struct data mobil ke dalam struct jalur
	struct jalur *next;
};
struct jalur *jalur_mobil[4]; // membuat jalur ke dalam array

// Menampilkan mobil terdapat pada jalur mana
struct jalur *display(struct jalur *head) {
    struct jalur *curr = head;
    while (curr != NULL) {
        printf("%s[%d]->", curr->dtm->plat_nomor, curr->dtm->jenis_mobil);
        curr = curr->next;
    }
    printf("NULL");
    return head;
}

//fungsi untuk memasukkan kendaraan ke dalam jalur
struct jalur *pushTail(struct jalur *head, struct data_mobil *kendaraan) {
    struct jalur *curr, *new_queue;
    new_queue = (struct jalur *) malloc(sizeof(struct jalur));
    new_queue->dtm = kendaraan;
    new_queue->next = NULL;
    if(head == NULL){
        head = new_queue;
    }else{
        curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_queue;
    }
    return head;
}

// Fungsi untuk menghilangkan data mobil dari antrian jalur
struct jalur *popHead(struct jalur *head) {
    struct jalur *curr;
    if (head != NULL){
        curr = head;
        head = head->next;
        free(curr);
    }
    return head;
}

//Menentukan waktu pengerjaan mobil yang nantinya dicatatkan ke dalam file 
int calculate_time(struct data_mobil *kendaraan){
    int total_waktu = 0;
    switch (kendaraan->jenis_mobil){
        case 1:
            if (kendaraan->layanan[0] == 1){
                total_waktu += 30;
            }

            if (kendaraan->layanan[1] == 1){
                total_waktu += 30;
            }

            if (kendaraan->layanan[2] == 1){
                total_waktu += 40;
            }
            break;
        case 2:
            if (kendaraan->layanan[0] == 1){
                total_waktu += 30;
            }

            if (kendaraan->layanan[1] == 1){
                total_waktu += 30;
            }

            if (kendaraan->layanan[2] == 1){
                total_waktu += 40;
            }
            break;
        case 3:
            if (kendaraan->layanan[0] == 1){
                total_waktu += 60;
            }

            if (kendaraan->layanan[1] == 1){
                total_waktu += 60;
            }

            if (kendaraan->layanan[2] == 1){
                total_waktu += 80;
            }
            break;
        case 4:
            if (kendaraan->layanan[0] == 1){
                total_waktu += 60;
            }

            if (kendaraan->layanan[1] == 1){
                total_waktu += 60;
            }
            break;
    }
    return total_waktu;
}

// Function untuk menentukan harga yang akan dicatatkan pada file transaksi
int calculate_cost(struct data_mobil *kendaraan){
    int total_cost = 0;
    switch (kendaraan->jenis_mobil){
        case 1:
            if (kendaraan->layanan[0] == 1){
                total_cost += 50;
            }

            if (kendaraan->layanan[1] == 1){
                total_cost += 35;
            }

            if (kendaraan->layanan[2] == 1){
                total_cost += 125;
            }
            break;
        case 2:
            if (kendaraan->layanan[0] == 1){
                total_cost += 60;
            }

            if (kendaraan->layanan[1] == 1){
                total_cost += 40;
            }

            if (kendaraan->layanan[2] == 1){
                total_cost += 150;
            }
            break;
        case 3:
            if (kendaraan->layanan[0] == 1){
                total_cost += 70;
            }

            if (kendaraan->layanan[1] == 1){
                total_cost += 50;
            }

            if (kendaraan->layanan[2] == 1){
                total_cost += 200;
            }
            break;
        case 4:
            if (kendaraan->layanan[0] == 1){
                total_cost += 70;
            }

            if (kendaraan->layanan[1] == 1){
                total_cost += 40;
            }
            break;
    }
    return total_cost;
}

// fungsi menginput data mobil 
struct data_mobil *input_mobil(){
	struct data_mobil *mobil_masuk = (struct data_mobil *) malloc (sizeof(struct data_mobil));
	printf("---------Mobil datang------------\n");
	printf("Masukkan plat mobil : ");
	scanf("%s", &mobil_masuk->plat_nomor);
	do{
    	printf("Jenis Kendaraan:\n1.Kecil\n2.Sedang\n3.Besar\n4.Truck");
        printf("\nJenis Kendaraan Anda[1-4] : ");
        scanf("%d", &mobil_masuk->jenis_mobil);
    }while ( mobil_masuk->jenis_mobil < 1 || mobil_masuk->jenis_mobil > 4 );
    do{
        printf("Layanan cuci [1 = ya, 0 = tidak] : ");
        scanf("%d", &mobil_masuk->layanan[0]);
    }while ( mobil_masuk->layanan[0] < 0 || mobil_masuk->layanan[0] > 1 );
    do{
        printf("Layanan vakum [1 = ya, 0 = tidak] : ");
        scanf("%d", &mobil_masuk->layanan[1]);
    }while ( mobil_masuk->layanan[1] < 0 || mobil_masuk->layanan[1] > 1 );
    if (mobil_masuk->jenis_mobil != 4){
        do{
            printf("Layanan poles [1 = ya, 0 = tidak] : ");
            scanf("%d", &mobil_masuk->layanan[2]);
        }while ( mobil_masuk->layanan[2] < 0 || mobil_masuk->layanan[2] > 1 );
    }else{
        mobil_masuk->layanan[2] = 0;
	}
	return mobil_masuk;
}

// menghitung banyak nya antrian pada jalur 
int count_queue(struct jalur *head){
    int count = 0;
    struct jalur *curr;
    curr = head;
    while (curr != NULL) {
        curr = curr->next;
        count++;
    }
    return count;
}

// Untuk mencatat transaksi-transaksi yang sudah dilakukan
void write_transaction(struct jalur *head){
    struct jalur *curr = head;
    FILE *data;
    data = fopen("transaksi.txt", "a");
    fprintf(
        data, "{Plat[%s];Jenis_Mobil[%d];Cuci[%d];Vakum[%d];Poles[%d];Waktu Pengerjaan[%d'];Payment[Rp.%d,000]}\n",
		curr->dtm->plat_nomor, 
        curr->dtm->jenis_mobil, 
        curr->dtm->layanan[0], 
        curr->dtm->layanan[1], 
        curr->dtm->layanan[2], 
        curr->dtm->waktu_pengerjaan, 
        curr->dtm->cost);
    fclose(data);
}

/* menentukan jalur yang didapat dari membandingkan beberapa jalur mobil jika 
suatu jalur dengan jumlah antrian lebih sedikit akan ditambahkan mobil baru*/ 

void slot_pushTail(struct data_mobil *mobil_masuk){
    if(count_queue(jalur_mobil[1]) < count_queue(jalur_mobil[2])){
        jalur_mobil[1] = pushTail(jalur_mobil[1], mobil_masuk);
    }else if(count_queue(jalur_mobil[3]) < count_queue(jalur_mobil[2])){
        jalur_mobil[3] = pushTail(jalur_mobil[3], mobil_masuk);
    }else if(count_queue(jalur_mobil[2]) < count_queue(jalur_mobil[1])){
        jalur_mobil[2] = pushTail(jalur_mobil[2], mobil_masuk);
    }else{
        jalur_mobil[1] = pushTail(jalur_mobil[1], mobil_masuk);
    }
}

//prosedur saat mobil selesai
void mobil_selesai(struct jalur *head, int j){
	struct jalur *curr;
	curr = head;
	curr->dtm->waktu_pengerjaan = calculate_time(curr->dtm);
	curr->dtm->cost = calculate_cost(curr->dtm);
	write_transaction(curr);
	jalur_mobil[j-1] = popHead(curr);
}

// fungsi untuk melihat history transaksi
void read_transaction(){
    char line[256];
    FILE *file = fopen("transaksi.txt", "r");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); 
    }
    fclose(file);
}

//prosedur saat mobil datang
void mobil_datang(){
    struct data_mobil *mobil_masuk = input_mobil();
    printf("\n=============Konfirmasi Data Kendaraan=============");
    printf("\nPlat Nomor Kendaraan : %s", mobil_masuk->plat_nomor);
	printf("\nJenis Kendaraan : %d", mobil_masuk->jenis_mobil);
    printf("\nLayanan cuci : %d", mobil_masuk->layanan[0]);
    printf("\nLayanan vakum : %d", mobil_masuk->layanan[1]);
    printf("\nLayanan poles : %d \n", mobil_masuk->layanan[2]);
    
    // Untuk memasukkan mobil pada queue sesuai dengan jenisnya
    switch (mobil_masuk->jenis_mobil){
        case 1:
            slot_pushTail(mobil_masuk);
            break;
        case 2:
            slot_pushTail(mobil_masuk);
            break;
        case 3:
            jalur_mobil[0] = pushTail(jalur_mobil[0], mobil_masuk);
            break;
        case 4:
            jalur_mobil[0] = pushTail(jalur_mobil[0], mobil_masuk);
            break;
    }
}

// alur utama program
int main(){
	int pilihan = -1;
	int j;
	while(pilihan != 0){
		printf("\n         Wash Wash\n");
		printf("\n==========================\n");
		printf("Menu:\n");
		printf("1.Mobil masuk\n");
		printf("2.Melihat jalur \n");
		printf("3.Mobil selesai \n");
		printf("4.History Transaksi \n");
		printf("5.Exit\n");
		printf("Masukkan pilihan:");
		scanf("%d",&pilihan);
		switch (pilihan){
		case 1:
			mobil_datang();
			break;
		case 2:
			printf("jalur mobil\n");
			printf("Plat nomor [jalur]");
			printf("\njalur 1:");
            jalur_mobil[0] = display(jalur_mobil[0]);
            printf("\njalur 2:");
            jalur_mobil[1] = display(jalur_mobil[1]);
            printf("\njalur 3:");
            jalur_mobil[2] = display(jalur_mobil[2]);
            printf("\njalur 4:");
            jalur_mobil[3] = display(jalur_mobil[3]);
			break;
		case 3:
			printf("Mobil selesai\n");
			printf("Masukkan jalur kendaraan selesai: ");
			scanf("%d",&j);
			mobil_selesai(jalur_mobil[j-1],j);
			break;
		case 4:
			printf("Melihat history transaksi\n");
			read_transaction();
			break;			
		case 5:
			return 0;
		default:
			printf("Pilihan tidak ada\n");
			break;
		}
	}
}
