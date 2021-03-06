import { Component, OnInit } from '@angular/core';
import { APIDataService } from '../apidata.service';
import { DomSanitizer } from '@angular/platform-browser';

@Component({
  selector: 'app-records',
  templateUrl: './records.component.html',
  styleUrls: ['./records.component.css']
})
export class RecordsComponent implements OnInit {

  records = [];

  constructor(private api: APIDataService, private domSanitizer: DomSanitizer) { }

  ngOnInit(): void {
    let observer = this.api.GetRequest('/obtenerPersonas').subscribe(res => {
      res.forEach(element => {
        this.records.push(element);       
      });    
      console.log(this.records);
      observer.unsubscribe();
    })
  }
}
