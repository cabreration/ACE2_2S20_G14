import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';

const httpOptions = {
  headers : new HttpHeaders({
    'Content-Type': 'application/json'
  })
};

const mockAddress = 'http://localhost:3000';
const httpAddress = 'http://18.218.183.200'; /* 'http://localhost:3000/' */

@Injectable({
  providedIn: 'root'
})

export class APIDataService {

  constructor(private httpClient: HttpClient) { }

  PostRequest(address: string, info: object): Observable<any> {
    console.log(`POST: ${address}`);
    return this.httpClient.post<any>(httpAddress + address, info, httpOptions);
  }

  GetRequest(address: string): Observable<any> {
    console.log(`GET: ${address}`);
    return this.httpClient.get<any>(httpAddress + address, httpOptions);
  }


}
