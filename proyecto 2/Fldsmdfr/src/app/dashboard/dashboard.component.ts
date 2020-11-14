import { Component, OnInit } from '@angular/core';
import { APIDataService } from '../apidata.service';
import { ChartDataSets, ChartOptions } from 'chart.js';
import { Color, Label } from 'ng2-charts';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent implements OnInit {

  avgTime = null;
  promedioHoras = null;
  promedioDias = null;

  // ----------------------------- First One
  public firstChartData = [
    { data: [], label: 'Promedio Visitantes por Hora' },
  ];
  public firstChartLabels = null;
  public firstChartOptions = {
    scaleShowVerticalLines: false,
    responsive: true
  }
  public ChartColors: Color[] = [
    {
      borderColor: 'black',
      backgroundColor: 'rgba(255,0,0,0.3)',
    },
  ];
  public firstChartLegend = true;
  public firstChartType = 'bar';
  // -----------------------------

  // ----------------------------- First One
  public secondChartData = [
    { data: [], label: 'Promedio Visitantes por Dia de la Semana' },
  ];
  public secondChartLabels = null;
  public secondChartOptions = {
    scaleShowVerticalLines: false,
    responsive: true
  }
  public secondChartLegend = true;
  public secondChartType = 'bar';
  // -----------------------------

  constructor(private api: APIDataService) { }

  ngOnInit(): void {
    let observer = this.api.GetRequest('/getTiempoPromedio').subscribe(res => this.avgTime = res.tiempoPromedio.toFixed(2))

    //let observer2 = this.api.GetRequest('/getConcurrenciaHoras').subscribe(res => console.log(res))

    let observer3 = this.api.GetRequest('/getPromedioHoras').subscribe(res => {
      console.log(res);
      this.promedioHoras = res.horas;
      this.prepareFirst();
    })

    let observer4 = this.api.GetRequest('/getConcurrenciaDias').subscribe(res => {
      console.log(res);
      this.promedioDias = res.dias;
      this.prepareSecond();
    })
  }

  prepareFirst() {
    this.firstChartLabels = []
    this.firstChartData[0].data = []
    this.promedioHoras.forEach(entry => {
      this.firstChartLabels.push(entry.hora);
      this.firstChartData[0].data.push(entry.personas.toFixed(2))
    });
  }

  prepareSecond() {
    this.secondChartLabels = []
    this.secondChartData[0].data = []
    this.promedioDias.forEach(entry => {
      this.secondChartLabels.push(entry.dia);
      this.secondChartData[0].data.push(entry.personas.toFixed(2))
    });
  }

}
