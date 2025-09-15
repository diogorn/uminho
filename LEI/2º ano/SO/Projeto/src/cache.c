#include <stdio.h>
#include "servidor_config.h"
#include <glib.h>
#include "cache.h"
#include <time.h>

typedef struct cache_frequency_entry {

    CacheEntry* entry;
    int frequency;

} CacheFrequencyEntry;

int compare_cache_entry_message(CacheEntry* cache_entry,mensagem msg) {

        if (cache_entry->tipo != msg.cmd)
            return 0;

        switch (msg.cmd) {

            case PEDIDO_GET:
                
                if (cache_entry->index == msg.index) {
                    return 1;
                }

                break;

            case PEDIDO_DELETE:
                
                if (cache_entry->index == msg.index) {
                    return 1;
                }

                break;

            case PEDIDO_INSERT:

                if (strcmp(cache_entry->titulo,msg.string1) == 0 && 
                    strcmp(cache_entry->autores,msg.string2) == 0 && 
                    cache_entry->year == msg.inteiro && 
                    strcmp(cache_entry->path,msg.string3) == 0) {
                    
                    return 1;
                    }

                break;

            case PEDIDO_LINES:
                
                if (strcmp(cache_entry->keyword,msg.string1) == 0 && 
                    cache_entry->index == msg.index) {
                    return 1;
                }

                break;

            case PEDIDO_LIST:
                
                if (strcmp(cache_entry->keyword,msg.string1) == 0) {
                    return 1;
                }

                break;

            default:
                return 0;
                break;

        }

    return 0;

}

void freeCacheEntry(CacheEntry* entry) {

    g_array_free(entry->indices,true);
    free(entry);

}

void printCacheEntry(CacheEntry* entry) {

    printf(">>>>>>>>>>>>>>\n");
    printf("Tipo : %d\n",entry->tipo);
    printf("Index : %d\n",entry->index);
    printf("Titulo : %s\n",entry->titulo);
    printf("Autores : %s\n",entry->autores);
    printf("Ano : %d\n",entry->year);
    printf("Path : %s\n",entry->path);
    printf("Keyword : %s\n",entry->keyword);
    printf("Número de linhas : %d\n",entry->n_linhas);
    printf("Número de indices: ");
    for (int i = 0 ; i < entry->indices->len ; i++) {
        int numero = g_array_index(entry->indices,int,i);
        printf("%d ",numero);
    }
    printf("\n");

    printf("<<<<<<<<<<<<<<\n");

}

// #######################
//          CRIAÇÃO          
// #######################

//Criar CACHE
Cache createCache(enum Cache_Tipo tipo, int max_entries) {

    Cache cache;

    cache.max_entries = max_entries;

    switch (tipo) {

        case CACHE_FIFO:

            cache.tipo_cache = CACHE_FIFO;
            cache.cache_fifo.queue = g_queue_new();
            
            break;

        case CACHE_TIME:
        
            cache.tipo_cache = CACHE_TIME;
            cache.cache_time.lista = NULL;
            cache.cache_time.mapa = g_hash_table_new(g_int_hash, g_int_equal);
            cache.cache_time.max_entries = max_entries;


            break;

        case CACHE_FREQUENCY:

            cache.tipo_cache = CACHE_FREQUENCY;
            cache.cache_frequency.lista = g_array_new(FALSE, FALSE, sizeof(CacheFrequencyEntry));

            break;


        default:

            cache.tipo_cache = NO_CACHE;

            break;

    }

    return cache;

}

// #######################
//          GET          
// #######################

CacheEntry* cache_fifo_get(CacheFIFO* cache,mensagem msg) {

    for (GList* l = cache->queue->head; l != NULL; l = l->next) {

        CacheEntry* dado = l->data;
    
        if (dado->tipo != msg.cmd)
            continue;
    
        if (compare_cache_entry_message(dado,msg) == 1) {
            return dado;
        }
    }

    return NULL;
}


CacheEntry* cache_frequency_get(CacheFrequency* cache,mensagem msg) {

    for (int i = 0; i < cache->lista->len ; i++) {

        CacheFrequencyEntry* entry = &(g_array_index(cache->lista,CacheFrequencyEntry,i));
        CacheEntry* dado = entry->entry;

        if (dado->tipo != msg.cmd)
            continue;

        if (compare_cache_entry_message(dado,msg) == 1) {
            entry->frequency++;
            return dado;
        }

    }

    return NULL;

}

CacheEntry* cache_time_get(CacheTime* cache, mensagem msg) {
    for (GList* l = cache->lista; l != NULL; l = l->next) {
        CacheEntry* dado = (CacheEntry*)l->data;
        if (dado->tipo != msg.cmd)
            continue;
        if (compare_cache_entry_message(dado, msg)) {
            cache->lista = g_list_remove_link(cache->lista, l);
            cache->lista = g_list_prepend(cache->lista, dado);
            g_hash_table_replace(cache->mapa, &dado->index, cache->lista);
            return dado;
        }
    }
    return NULL;
}

//Função que busca um item na cache
CacheEntry* cache_get(Cache* cache,mensagem msg) {

    switch (cache->tipo_cache) {

        case CACHE_FIFO:

            return cache_fifo_get(&(cache->cache_fifo),msg);
            break;

        case CACHE_TIME:

            return cache_time_get(&(cache->cache_time), msg);
            break;

        case CACHE_FREQUENCY:

            return cache_frequency_get(&(cache->cache_frequency),msg);
            break;


        default:
            return NULL;
            break;

    }

    return NULL;

}

// #######################
//          INSERT          
// #######################

void cache_fifo_insert(CacheFIFO* cache, CacheEntry* entry, int max_entries) {

    if (g_queue_get_length(cache->queue) >= max_entries) {

        gpointer antigo = g_queue_pop_head(cache->queue);
        free(antigo);
    }

    g_queue_push_tail(cache->queue, entry);

}


void cache_frequency_insert(CacheFrequency* cache,CacheEntry* entry, int max_entries) {

    int novo_indice = 0;
    int min_frequencia = 9999;

    if (cache->lista->len >= max_entries) {

        for (int i = 0; i < cache->lista->len ; i++) {

            CacheFrequencyEntry entry_index = g_array_index(cache->lista,CacheFrequencyEntry,i);

            if (entry_index.frequency < min_frequencia) {
                min_frequencia = entry_index.frequency;
                novo_indice = i;
            }

        }

        CacheFrequencyEntry new_entry;
        new_entry.entry = entry;
        new_entry.frequency = 1;
        g_array_remove_index(cache->lista, novo_indice);
        g_array_insert_val(cache->lista, novo_indice, new_entry);


    }
    else {

        CacheFrequencyEntry new_entry;
        new_entry.entry = entry;
        new_entry.frequency = 1;
        g_array_append_val(cache->lista,new_entry);

    }

}

void cache_time_insert(CacheTime* cache, CacheEntry* entry, int max_entries) {
    int* key = malloc(sizeof(int));
    *key = entry->index;

    GList* node = g_hash_table_lookup(cache->mapa, key);
    if (node) {
        cache->lista = g_list_remove_link(cache->lista, node);
        cache->lista = g_list_prepend(cache->lista, entry);
        g_hash_table_replace(cache->mapa, key, cache->lista);
        free(key);
        return;
    }

    if (g_list_length(cache->lista) >= max_entries) {
        GList* last = g_list_last(cache->lista);
        CacheEntry* last_entry = last->data;
        cache->lista = g_list_remove_link(cache->lista, last);
        g_hash_table_remove(cache->mapa, &last_entry->index);

        free(last);
        freeCacheEntry(last_entry);
        g_list_free(last);
    }

    cache->lista = g_list_prepend(cache->lista, entry);
    g_hash_table_insert(cache->mapa, key, cache->lista);
    free(key);

    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("CACHE TIME (LRU):\n");
    for (GList* l = cache->lista; l != NULL; l = l->next) {
        CacheEntry* current = (CacheEntry*)l->data;
        printCacheEntry(current);
    }
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void cache_insert(Cache* cache,CacheEntry* entry) {

    //Filtrar mensagens
    // Tipo tem que ser: DELETE | GET | LINES
    if (entry->tipo != PEDIDO_DELETE && entry->tipo != PEDIDO_GET && entry->tipo != PEDIDO_LINES)
        goto eliminar_mensagem;

    switch (cache->tipo_cache) {

        case CACHE_FIFO:
            cache_fifo_insert(&(cache->cache_fifo), entry, cache->max_entries);
            return;
            break;

        case CACHE_TIME:
            cache_time_insert(&(cache->cache_time), entry, cache->max_entries);
            return;
            break;

        case CACHE_FREQUENCY:
            cache_frequency_insert(&(cache->cache_frequency),entry,cache->max_entries);
            return;
            break;

        default:
            break;

    }

eliminar_mensagem:

    //Entrada tem que ser eliminada
    freeCacheEntry(entry);

    return;

}

// #######################
//          FILTER          
// #######################


void cache_fifo_filter(CacheFIFO* cache, CacheEntry* entry, int max_entries) {

    for (int i = cache->queue->length - 1; i >= 0; i--) {
        CacheEntry* atual = g_queue_peek_nth(cache->queue, i);
        if (atual != NULL && atual->index == entry->index) {
            g_queue_remove(cache->queue, atual);
            freeCacheEntry(atual);
        }
    }
    
}


void cache_frequency_filter(CacheFrequency* cache,CacheEntry* entry, int max_entries) {

    for (int i = cache->lista->len - 1; i >= 0 ; i--) {

        CacheFrequencyEntry entry_index = g_array_index(cache->lista,CacheFrequencyEntry,i);
        CacheEntry* entry_obtido = entry_index.entry;

        //Mesmo indice
        if (entry_obtido->index == entry->index) {
            freeCacheEntry(entry_obtido);
            g_array_remove_index(cache->lista,i);
        }

    }

}

void cache_time_filter(CacheTime* cache, CacheEntry* entry, int max_entries) {
    GList* node = g_hash_table_lookup(cache->mapa, &entry->index);
    if (node) {
        CacheEntry* dado = (CacheEntry*)node->data;
        cache->lista = g_list_remove_link(cache->lista, node);
        g_hash_table_remove(cache->mapa, &entry->index);
        freeCacheEntry(dado);
        g_list_free(node);
    }

    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("CACHE TIME:\n");
    for (GList* l = cache->lista; l != NULL; l = l->next) {
        printCacheEntry((CacheEntry*)l->data);
    }
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void cache_filter(Cache* cache,CacheEntry* entry) {

    //Filtrar mensagens
    // Tipo tem que ser: DELETE
    if (entry->tipo != PEDIDO_DELETE)
        return;

    switch (cache->tipo_cache) {

        case CACHE_FIFO:
            cache_fifo_filter(&(cache->cache_fifo), entry, cache->max_entries);
            return;
            break;

        case CACHE_TIME:
            cache_time_filter(&(cache->cache_time), entry, cache->max_entries);
            return;
            break;

        case CACHE_FREQUENCY:
            cache_frequency_filter(&(cache->cache_frequency),entry,cache->max_entries);
            break;

        default:
            break;

    }

    return;

}