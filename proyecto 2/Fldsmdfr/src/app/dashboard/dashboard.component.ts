import { Component, OnInit } from '@angular/core';
import { APIDataService } from '../apidata.service';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent implements OnInit {

  constructor(private api: APIDataService) { }

  ngOnInit(): void {
    let observer = this.api.GetRequest('/getTiempoPromedio').subscribe(res => console.log(res))

    let observer2 = this.api.GetRequest('/getConcurrenciaHoras').subscribe(res => console.log(res))

    let observer3 = this.api.GetRequest('/getPromedioHoras').subscribe(res => console.log(res))
  }

}
