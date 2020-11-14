import { Component, OnInit } from '@angular/core';
import { APIDataService } from '../apidata.service';

@Component({
  selector: 'app-registry',
  templateUrl: './registry.component.html',
  styleUrls: ['./registry.component.css']
})

export class RegistryComponent implements OnInit {

  name: string = null;
  dpi: string = null;
  photo = null;

  constructor(private api: APIDataService) { }

  ngOnInit(): void {
  }

  sendRecord() {
    if (this.name == null || this.name == '') {
      alert('Debe ingresar su nombre!');
      return;
    }
    else if (this.dpi == null || this.dpi == '') {
      alert('Debe ingresar su numero de dpi!');
    }

    let user = {
      nombre: this.name,
      dpi: Number(this.dpi),
      base64: 'lnfanfasdlkjnasdlkfnaskljdfnaskljfdnsalkjdfnsa'
    }

    let observer = this.api.PostRequest('/UserInfo', user).subscribe(res => {
      console.log(res);
      observer.unsubscribe();
    })

    this.name = '';
    this.dpi= '';
  }

}
